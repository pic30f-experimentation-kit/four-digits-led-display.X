#ifndef DISPLAY_H
#define	DISPLAY_H

#define DISPLAY_POSITIONS 4

/**
 * Provides the position of the display to lit. 
 * @return The position of the display. 0 is the most significant position,
 * and #DISPLAY_POSITIONS - 1 is the least significant position.
 */
int displayPosition();

/**
 * The digit to display, in base 10 binary.
 * @return The digit to display.
 */
int displayDigit();

/**
 * Call this method to switch to the next display position.
 * This will change the values returned by {@link #displayPosition}
 * and {@link #displayDigit}
 */
void displayNext();

/**
 * Sets the value to display.
 * When displayed in base 10, it should be represented with
 * {@link #DISPLAY_POSITION} digits or less.
 * @param value The value to display.
 */
void displaySetValue(int value);

#ifdef TEST

/**
 * Performs unit testing on this library
 */
void testDisplay();

#endif

#endif	/* DISPLAY_H */

