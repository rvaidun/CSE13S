#include "io.h"

#include "bitlib.h"
#include "code.h"
#include "stdio.h" // For main can remove later.

#include <fcntl.h>
#include <unistd.h>
static uint8_t buf[BLOCK];
static uint32_t bit_index = 0;
static uint32_t end_buffer = 0;
uint64_t bytes_written = 0;
uint64_t bytes_read = 0;

// Loops calls to the read syscall function
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0; // Number of bytes read so far
    int bytes = -2; // Number of bytes that were read by read()
    while ((bytes > 0 || bytes == -2) && total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
    }
    bytes_read += total;
    return total;
}

// Loops calls to the write syscall function
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = -2;

    while ((bytes > 0 || bytes == -2) && total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }
    bytes_written += total;
    return total;
}

// Flushes codes
void flush_codes(int outfile) {
    uint32_t bytes = bit_index / 8;
    uint8_t mask = (1 << (bit_index % 8)) - 1; // Mask for bits to preserve
    if (mask) {
        buf[bytes++] &= mask;
    }
    write_bytes(outfile, buf, bytes);
}

// Returns one bit at a time through the pointer for bit. Reads infile to the buffer
bool read_bit(int infile, uint8_t *bit) {
    // Only read when we have finished with the buffer
    if (bit_index == 0) {
        end_buffer = read_bytes(infile, buf, BLOCK) * 8;
    }

    *bit = get_bit(buf, bit_index);
    bit_index = (bit_index + 1) % (BLOCK * 8);

    // At the end of file return false
    if (bit_index > end_buffer) {
        return false;
    } else {
        return true;
    }
}

// Writes codes to the buffer
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {

        // If get_bit returns one then set the bit in the buffer
        // Else clear the bot
        // Buffer is like a bit vector
        if (get_bit(c->bits, i) == 1) {
            set_bit(buf, bit_index);
        } else {
            clr_bit(buf, bit_index);
        }

        bit_index++; // Increment index

        // If bufer is full right it
        if (bit_index == 8 * BLOCK) {
            write_bytes(outfile, buf, BLOCK);
            bit_index = 0;
        }
    }
}
