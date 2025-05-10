#ifndef TEST_H
#define	TEST_H

#ifdef TEST

/** Initializes test bench. */
void initializeTests();

/**
 * Asserts that actual and expected values are equal.
 * @param testId Test identifier.
 * @param actual Actual value.
 * @param expected Expected value.
 */
unsigned char assertEquals(const char *testId, int actual, int expected);

/**
 * Asserts that actual value is within the defined limits.
 * @param testId Test identifier.
 * @param actual Actual value.
 * @param min Actual value must be greater or equal min value.
 * @param max Actual value must be lesser or equal max value.
 */
unsigned char assertWithinBounds(const char *testId, int actual, int min, int max);

/**
 * Asserts that actual value is not zero.
 * @param testId Test identifier.
 * @param actual Actual value.
 */
unsigned char assertNotZero(const char *testId, int actual);

/** Ends test and reports errors. */
void reportTests();

#endif
#endif

