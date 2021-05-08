#include "bm.h"
#include "hamming.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> // For getopt
#define OPTIONS "hi:o:"

void print_help(void) {
    printf("SYNOPSIS\n"
           "   A Hamming(8, 4) systematic code generator.\n"
           "USAGE\n"
           "   ./encode [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h              Display program help and usage.\n"
           "   -i infile      Input data to encode (default: stdin)\n"
           "   -o outfile     Output of encoded data (default: stdout)\n");
    return;
}
// Code from assignment PDF
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Code from assignment PDF
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Code from assignment PDF
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    FILE *in_fp = stdin;
    FILE *out_fp = stdout;
    struct stat statbuf;
    uint8_t table[15];
    for (int i = 0; i < 15; i++) {
        table[i] = 0;
    }
    int c;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            in_fp = fopen(optarg, "r");
            if (in_fp == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return -1;
            }
            break;

        case 'o':
            out_fp = fopen(optarg, "wb");
            if (out_fp == NULL) {
                fprintf(stderr, "Error opening file to write\n");
                return -1;
            }
            break;
        default: print_help(); return -1;
        }
    }

    // Code to change file permissions from assignment PDF
    fstat(fileno(in_fp), &statbuf);
    fchmod(fileno(out_fp), statbuf.st_mode);

    BitMatrix *bm = bm_create(4, 8);
    bm_set_bit(bm, 0, 0);
    bm_set_bit(bm, 0, 5);
    bm_set_bit(bm, 0, 6);
    bm_set_bit(bm, 0, 7);
    bm_set_bit(bm, 1, 1);
    bm_set_bit(bm, 1, 4);
    bm_set_bit(bm, 1, 6);
    bm_set_bit(bm, 1, 7);
    bm_set_bit(bm, 2, 2);
    bm_set_bit(bm, 2, 4);
    bm_set_bit(bm, 2, 5);
    bm_set_bit(bm, 2, 7);
    bm_set_bit(bm, 3, 3);
    bm_set_bit(bm, 3, 4);
    bm_set_bit(bm, 3, 5);
    bm_set_bit(bm, 3, 6);

    while ((c = fgetc(in_fp)) != EOF) {
        fputc(ham_encode(bm, lower_nibble(c)), out_fp);
        fputc(ham_encode(bm, upper_nibble(c)), out_fp);
    }
}
