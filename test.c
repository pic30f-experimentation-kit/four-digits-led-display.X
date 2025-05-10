#ifdef TEST
#include <xc.h>
#include <stdio.h>
#include "test.h"

/**
 * Sends a char to the UART.
 * This method is called by <code>printf</code> behind the scenes.
 * If a terminal is connected to RX / TX, or simulator is configured to output
 * UART 1, then text is displayed.
 * @param data Ascii code of the char to display.
 */
void putch(char data) {
    while( ! U1STAbits.UTXBF);
    U1TXREG = data;
}

/**
 * Initializes UART for asynchronous output.
 */
void initializeUART1() {
    // Initialize the UxBRG register for the appropriate baud rate.
    U1BRG = 95;
    
    // Set the number of data bits, number of Stop bits, and parity selection.
    // The most common data format is 8 bits, no parity and one Stop
    // bit (denoted as 8, N, 1), which is the default (POR) setting.
    U1MODEbits.PDSEL = 0;   // 8 Bits, no parity
    U1MODEbits.STSEL = 0;   // 1 Stop bit.
    
    // Simulator UART is connected to the regular pins
    U1MODEbits.ALTIO = 0;   // Use regular pins - U1TX / U1RX

    // Enable UART1:
    U1MODEbits.UARTEN = 1;  // Enable UART1
    U1STAbits.UTXEN = 1;    // Enable UART1 transmitter (after enabling UART).
    
}

/** Number of failed tests, since initialization. */
static int failedTests = 0;

/** Number of passed tests, since initialization. */
static int passedTests = 0;

void initializeTests() {
    initializeUART1();
    failedTests = 0;
    passedTests = 0;
    printf("\r\nStarting tests...\r\n");
}

unsigned char assertEquals(const char *testId, int actual, int expected) {
    if (actual != expected) {
        printf("Test %s: actual [%d], expected [%d]\r\n",
                testId, actual, expected);
        failedTests ++;
        return 1;
    } else {
        passedTests ++;
    }
    return 0;
}

unsigned char assertWithinBounds(const char *testId, int actual, int min, int max) {

    if ( (actual < min) || (actual > max) ) {
        printf("Test %s: actual [%d] outside bounds: [%d] to [%d]\r\n",
                testId, actual, min, max);
        failedTests ++;
        return 1;
    } else {
        passedTests ++;
    }
    return 0;
}

unsigned char assertNotZero(const char *testId, int actual) {
    if (actual == 0) {
        printf("Test %s: actual is zero, but it should not.\r\n", testId);
        failedTests ++;
        return 1;
    } else {
        passedTests ++;
    }
    return 0;
}

void reportTests() {
    printf("%d passed tests\r\n", passedTests);
    printf("%d failed tests\r\n", failedTests);
}


#endif
