#include "buffer.h"
#include "test.h"

void bufferInitialize(Buffer *buffer) {
    buffer->in = 0;
    buffer->out = 0;
}

void bufferAdd(Buffer *buffer, int value) {
    buffer->buffer[buffer->in] = value;
    buffer->in++;
    if (buffer->in >= BUFFER_SIZE) {
        buffer->in = 0;
    }
}

int bufferRead(Buffer *buffer) {
    if (bufferIsEmpty(buffer)) {
        return 0;
    }
    int value = buffer->buffer[buffer->out];
    buffer->out++;
    if (buffer->out > BUFFER_SIZE) {
        buffer->out = 0;
    }
    return value;
}

int bufferIsEmpty(Buffer *buffer) {
    if (buffer->in == buffer->out) {
        return -1;
    }
    return 0;
}

#ifdef TEST
void buffer_can_add_and_retrieve_values() {
    Buffer buffer;
    bufferInitialize(&buffer);
    
    bufferAdd(&buffer, 10);
    bufferAdd(&buffer, 11);
    bufferAdd(&buffer, 12);
    bufferAdd(&buffer, 13);

    assertEquals("BUF_RET_1", bufferRead(&buffer), 10);
    assertEquals("BUF_RET_2", bufferRead(&buffer), 11);
    assertEquals("BUF_RET_3", bufferRead(&buffer), 12);
    assertEquals("BUF_RET_4", bufferRead(&buffer), 13);    
}

void buffer_returns_zero_when_empty() {
    Buffer buffer;
    bufferInitialize(&buffer);
    
    assertEquals("BUF_EMP_1", bufferRead(&buffer), 0);
    bufferAdd(&buffer, 10);
    bufferAdd(&buffer, 11);
    bufferRead(&buffer);
    bufferRead(&buffer);
    assertEquals("BUF_EMP_2", bufferRead(&buffer), 0);
}

void testBuffer() {
    buffer_can_add_and_retrieve_values();
    buffer_returns_zero_when_empty();
}

#endif
