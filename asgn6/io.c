#include "io.h"

#include "code.h"
#include "stdio.h" // For main can remove later.

#include <fcntl.h>
#include <unistd.h>

static uint8_t buf[BLOCK];
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
    int total = 0; // Number of bytes read so far
    int bytes = -2; // Number of bytes that were read by read()
    while ((bytes > 0 || bytes == -2) && total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = -2;

    while ((bytes > 0 || bytes == -2) && total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

void flush_codes(int outfile) {
    uint32_t bytes = bit_index / 8;
    if (bit_index % 8 != 0) {
        bytes++;
    }
    write_bytes(outfile, buf, bytes);
}

bool read_bit(int infile, uint8_t *bit) {
    uint32_t end_buffer = read_bytes(infile, buf, BLOCK) * 8;

    *bit = get_bit(buf, bit_index);
    // printf(" BEFORE bit_index %d\n bits_in_buffer %d\n", bit_index, bits_in_buffer);
    bit_index = (bit_index + 1) % (BLOCK * 8);
    // printf(" AFTER bit_index %d\n bits_in_buffer %d\n", bit_index, bits_in_buffer);
    if (bit_index > end_buffer) {
        // printf("SECOND bit_index %d\n bits_in_buffer %d\n", bit_index, bits_in_buffer);
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (get_bit(c->bits, i) == 1) {
            set_bit(buf, bit_index);
        } else {
            clr_bit(buf, bit_index);
        }
        bit_index++;
        if (bit_index == 8 * BLOCK) {
            write_bytes(outfile, buf, BLOCK);
            bit_index = 0;
        }
    }
    flush_codes(outfile);
}
// int main(void) {
//     printf("test\n");
//     int h = open("test.txt", O_RDONLY);
//     int b = read_bytes(h, buf, BLOCK);
//     for (int i = 0; i < b; i++) {
//         printf("%c", buf[i]);
//     }
//     printf("\n");
// }
