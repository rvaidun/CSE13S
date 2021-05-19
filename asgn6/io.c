#include "io.h"

#include <fcntl.h>
#include <unistd.h>

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int i = 0;
    for (i = 0; i < nbytes;) {
        int t = read(infile, buf + i, nbytes);
        i += t;
        if (i == -1) {
            break;
        }
    }
    return i;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int i = 0;
    for (i = 0; i < nbytes;) {
        int t = write(outfile, buf + i, nbytes);
        if (i == -1) {
            break;
        }
        i += t;
    }
    return i;
}

uint8_t get_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    return (v[bytepos] >> bitpos) & 1;
}

void set_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] |= (1 << bitpos);
    return;
}

bool read_bits(int infile, uint8_t *bits) {
    static uint8_t buf[BLOCK];
    int nbytes = *bits / 8;
    if (*bits % 8 != 0) {
        nbytes += 1;
    }
    for (int i = 0; i < nbytes;) {
        int bytes_read = read_bytes(infile, buf, nbytes);
        for (int j = 0; j < bytes_read; j++) {
            uint8_t bit = get_bit(buf, i + j);
            bits[i + j] = bit;
            i++;
        }
    }
}

void write_code(int outfile, Code *c) {
    static uint8_t buf[BLOCK];
    for (int i = 0; i < c->top; i++) {
        set_bit(buf, i);
    }
    int total_bytes = c->top / 8;
    if (c->top % 8 != 0) {
        total_bytes += 1;
    }
    for (int i = 0; i < total_bytes;) {
        int bytes_written = write(outfile, buf, total_bytes);
        i += bytes_written;
    }
}

void flush_codes(int outfile) {
    printf("Not implemented yet");
}
