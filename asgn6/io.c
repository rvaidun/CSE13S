#include "io.h"

#include <fcntl.h>
#include <unistd.h>

static uint8_t buf[BLOCK];
static uint32_t bits_in_buffer = 0;
static uint32_t bit_index = 0;

void set_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] |= (1 << bitpos);
    return;
}

void clr_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] &= ~(1 << bitpos);
    return;
}

uint8_t get_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    return (v[bytepos] >> bitpos) & 1;
}

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total; // Number of bytes read so far
    int bytes; // Number of bytes that were read by read()
    while (bytes > 0 && total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
        bits_in_buffer += bytes * 8;
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total;
    int bytes;

    while (bytes > 0 && total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

void flush_codes(int outfile) {
    uint32_t bytes = bits_in_buffer / 8;
    if (bits_in_buffer % 8 != 0) {
        bytes++;
    }
    write_bytes(outfile, buf, bytes);
}

bool read_bit(int infile, uint8_t *bit) {
    if (bit_index == 0) {
        bits_in_buffer = 0;
        int bytes = read_bytes(infile, buf, BLOCK);
    }
    *bit = get_bit(buf, bit_index);
    bit_index = (bit_index + 1) % BLOCK * 8;
    if (bit_index > bits_in_buffer) {
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    for (int i = 0; i < code_size(c); i++) {
        if (get_bit(c->bits, i) == 1) {
            set_bit(buf, i);
        } else {
            clr_bit(buf, i);
        }
        bit_index++;
        if (bit_index == 8 * BLOCK) {
            write_bytes(outfile, buf, BLOCK);
            bit_index = 0;
        }
    }
    flush_codes(outfile);
}
