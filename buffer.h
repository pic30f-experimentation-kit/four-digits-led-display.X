#ifndef BUFFER_H
#define	BUFFER_H

#define BUFFER_SIZE 32

/**
 * A type of BUFFER
 */
typedef struct {
    int in;
    int out;
    int buffer[BUFFER_SIZE];
} Buffer;

/**
 * Initializes the buffer.
 * Call this method before any other operation with a buffer.
 * @param buffer The buffer.
 */
void bufferInitialize(Buffer *buffer);

/**
 * Adds value to the buffer
 * @param buffer The buffer
 * @param value The value to add.
 */
void bufferAdd(Buffer *buffer, int value);

/**
 * Reads one value from the buffer.
 * @param buffer The buffer.
 * @return The read value.
 */
int bufferRead(Buffer *buffer);

/**
 * Checks whether the buffer is empty.
 * @param buffer The buffer.
 * @return <code>-1</code> if the buffer is empty.
 */
int bufferIsEmpty(Buffer *buffer);

#ifdef TEST

/**
 * Tests buffer library.
 */
void testBuffer();

#endif

#endif

