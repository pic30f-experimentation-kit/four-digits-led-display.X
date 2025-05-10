#include "display.h"
#include "test.h"

static char digits[DISPLAY_POSITIONS];

static int position = 0;

void displayInit() {
    position = 0;
}

int displayPosition() {
    return position;
}

int displayDigit() {
    return digits[position];
}

void displayNext() {
    position++;
    if (position >= DISPLAY_POSITIONS) {
        position = 0;
    }
}

void displaySetValue(int value) {
    for(int n = 0; n < DISPLAY_POSITIONS; n++) {
        digits[n] = value % 10;
        value /= 10;
    }
}

#ifdef TEST
void display_can_render_a_4_digit_number() {
    displayInit();
    displaySetValue(1234);

    assertEquals("DISP_4_1STP", displayPosition(), 0);
    assertEquals("DISP_4_1STD", displayDigit(), 4);
    displayNext();

    assertEquals("DISP_4_2NDP", displayPosition(), 1);
    assertEquals("DISP_4_2NDD", displayDigit(), 3);
    displayNext();

    assertEquals("DISP_4_3RDP", displayPosition(), 2);
    assertEquals("DISP_4_3RDD", displayDigit(), 2);
    displayNext();

    assertEquals("DISP_4_4THP", displayPosition(), 3);
    assertEquals("DISP_4_4THD", displayDigit(), 1);
    displayNext();
}

void display_can_render_a_2_digit_number() {
    displayInit();
    displaySetValue(34);

    assertEquals("DISP_2_1STP", displayPosition(), 0);
    assertEquals("DISP_2_1STD", displayDigit(), 4);
    displayNext();

    assertEquals("DISP_2_2NDP", displayPosition(), 1);
    assertEquals("DISP_2_2NDD", displayDigit(), 3);
    displayNext();

    assertEquals("DISP_2_3RDP", displayPosition(), 2);
    assertEquals("DISP_2_3RDD", displayDigit(), 0);
    displayNext();

    assertEquals("DISP_2_4THP", displayPosition(), 3);
    assertEquals("DISP_2_4THD", displayDigit(), 0);
    displayNext();

}

void testDisplay() {
    display_can_render_a_4_digit_number();
    display_can_render_a_2_digit_number();
}
#endif
