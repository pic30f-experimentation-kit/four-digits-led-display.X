#include <xc.h>
#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD         // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF         // Disable watchdog

#include "display.h"
#include "buffer.h"
#include "test.h"

static Buffer buffer;

#ifndef TEST
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void) {
    static int capture = 0;
    
    // Reset the interruption flag:
    IFS0bits.ADIF = 0;

    // Averages all available input captures, to remove noise:
    unsigned int average = 0;
    volatile unsigned int *adcptr = &ADCBUF0;
    for(int n = 0; n < 16; n++) {
        average += *adcptr;
        adcptr++;
    }
    average >>= 4;
    
    // Place a breakpoint inside the conditional section to stop
    // the program every time the stimulus changes.
    if (average != capture) {
        capture = average;
        bufferAdd(&buffer, average);
    }
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    // Reset the interruption flag.
    IFS0bits.T2IF = 0;
    
    int position = displayPosition();
    position <<= 4;
    PORTF = position;
    
    PORTB = displayDigit();
    
    displayNext();
}

void initializeADModule() {
    // Configure the A/D module
    // -> Select voltage reference source to match expected range 
    //    on analog inputs:
    ADCON2bits.VCFG = 0; // Use VRef+ = AVdd and VRef- = AVss
    
    // -> Select the analog conversion clock to match desired data rate with
    //    processor clock: FRC = 7.32MHz, PLL=x16 -> Fosc = 117.92MHz -> Tcy = 33.92ns
    ADCON3bits.ADCS = 63; // TAD = Tcy * (ADCS + 1) / 2 = 1102µs
    
    // -> Determine how sampling will occur
    ADCON1bits.ASAM = 1;  // Enable automating sampling.
    ADCON1bits.SSRC = 7;  // Use internal timer.
    
    // -> Determine how inputs will be allocated to the S/H channel
    TRISBbits.TRISB6 = 1; // AN6/RB6 is configured as input.
    ADPCFGbits.PCFG6 = 0; // AN6/RB6 is configured as analog.
    ADCHSbits.CH0NA = 0;  // Negative input is VRef-
    ADCHSbits.CH0SA = 6;  // Sample analog data from AN6.
    
    // -> Select how conversion results are presented in the buffer
    ADCON1bits.FORM = 0;  // Positive integer.
    ADCON2bits.SMPI = 15; // 16 samples per interrupt.

    // -> Select interrupt rate
    ADCON3bits.SAMC = 31; // Configure internal timer to allow 32TAD for sampling time.
    
    // -> Turn on A/D module
    ADCON1bits.ADON = 1;
    
    // Configure A/D interrupt (if required)
    // -> Clear ADIF bit
    IFS0bits.ADIF = 0;
    
    // -> Select A/D interrupt priority
    IPC2bits.ADIP = 1; // Lowest possible interrupt level
    IEC0bits.ADIE = 1; // Enable interrupts for A/D module
}

void initializeIOForDisplayModule() {
    // Initialize the related IO ports:
    TRISBbits.TRISB0 = 0; // RB0 is output.
    TRISBbits.TRISB1 = 0; // RB1 is output.
    TRISBbits.TRISB2 = 0; // RB2 is output.
    TRISBbits.TRISB3 = 0; // RB3 is output.
    ADPCFGbits.PCFG0 = 1; // AN0/RB0 is configured as analog.
    ADPCFGbits.PCFG1 = 1; // AN1/RB1 is configured as analog.
    ADPCFGbits.PCFG2 = 1; // AN2/RB2 is configured as analog.
    ADPCFGbits.PCFG3 = 1; // AN3/RB3 is configured as analog.

    TRISFbits.TRISF4 = 0; // RF4 is output.
    TRISFbits.TRISF5 = 0; // RF5 is output.
    TRISFbits.TRISF6 = 0; // RF6 is output.
    
    // Initialize timer
    T2CONbits.TSIDL = 0;  // Discontinue timer when device enters Idle mode.
    T2CONbits.TGATE = 0;  // Disable Time Gate Accumulation mode.
    T2CONbits.T32 = 0;    // Disable 32 timer mode.
    T2CONbits.TCS = 0;    // Clock source is Fosc/4
    T2CONbits.TCKPS = 2;  // Set the pre-scaler at 1/64.
    PR2 = 2303;           // 5ms interval at selected Fosc and pre-scaler.
    T2CONbits.TON = 1;    // Enable timer 2.
    
    IFS0bits.T2IF = 0;    // Clear timer 2 interrupt flag.
    IPC1bits.T2IP = 1;    // Lowest possible interrupt level.
    IEC0bits.T2IE = 1;    // Enable timer 2 interrupts
}


int main(void) {
    initializeADModule();
    initializeIOForDisplayModule();
    for(;;) {
        while(bufferIsEmpty(&buffer));
        displaySetValue(bufferRead(&buffer));
    }
}

#else
int main() {
    initializeTests();
    testDisplay();
    testBuffer();
    reportTests();
    while(1);
}
#endif