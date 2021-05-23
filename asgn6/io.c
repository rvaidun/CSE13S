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

void flush_codes(int outfile) {
    uint32_t bytes = bit_index / 8;
    uint8_t mask = (1 << (bit_index % 8)) - 1;
    if (mask) {
        buf[bytes++] &= mask;
    }
    write_bytes(outfile, buf, bytes);
}

bool read_bit(int infile, uint8_t *bit) {
    if (bit_index == 0) {
        end_buffer = read_bytes(infile, buf, BLOCK) * 8;
    }
    // printf("%x", buf[0]);
    *bit = get_bit(buf, bit_index);
    bit_index = (bit_index + 1) % (BLOCK * 8);
    if (bit_index > end_buffer) {
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
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
