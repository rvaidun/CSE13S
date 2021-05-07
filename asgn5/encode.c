#include "bm.h"
#include "bmbytes.h"
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
           "./encode [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h              Display program help and usage.\n"
           "   -i infile      Input containing graph (default: stdin)\n"
           "   -o outfile     Output of computed path (default: stdout)\n");
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

    uint8_t ln;
    uint8_t un;
    uint8_t c;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            in_fp = fopen(optarg, "rb");
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

    uint8_t generator_matrix[] = { 0xe1, 0xd2, 0xb4, 0x78 };
    BitMatrix *bm = bm_from_data_array(generator_matrix, 4);

    while ((c = fgetc(in_fp) != EOF)) {
        ln = encode(bm, lower_nibble(c));
        un = encode(bm, upper_nibble(c));
        fputc(encode(bm, lower_nibble(c)), out_fp);
        fputc(encode(bm, upper_nibble(c)), out_fp);
    }
}
