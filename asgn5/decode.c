#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> // For getopt
#define OPTIONS "hvi:o:"

void print_help(void) {
    printf("SYNOPSIS\n"
           "   A Hamming(8, 4) systematic code decoder.\n"
           "USAGE\n"
           "   ./decode [-h] [-v] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h              Display program help and usage.\n"
           "   -v             Print statistics of decoding to stderr.\n"
           "   -i infile      Input data to encode (default: stdin)\n"
           "   -o outfile     Output of decoded data (default: stdout)\n");
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

void count_stats(HAM_STATUS hs, uint32_t *bp, uint32_t *c, uint32_t *e) {
    *bp += 1;
    switch (hs) {
    case HAM_ERR: *e += 1; break;
    case HAM_CORRECT: *c += 1; break;
    default: break;
    }
}

int main(int argc, char **argv) {
    bool verbose = false;
    FILE *in_fp = stdin;
    FILE *out_fp = stdout;
    struct stat statbuf;

    int lnc;
    int unc;
    uint8_t lnm;
    uint8_t unm;
    HAM_STATUS hs;
    uint32_t bytes_processed = 0;
    uint32_t corrections = 0;
    uint32_t uncorrected_errors = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v': verbose = true; break;
        case 'i':
            in_fp = fopen(optarg, "rb");
            if (in_fp == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return -1;
            }
            break;

        case 'o':
            out_fp = fopen(optarg, "w");
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
    BitMatrix *bm = bm_create(8, 4);
    bm_set_bit(bm, 0, 1);
    bm_set_bit(bm, 0, 2);
    bm_set_bit(bm, 0, 3);
    bm_set_bit(bm, 1, 0);
    bm_set_bit(bm, 1, 2);
    bm_set_bit(bm, 1, 3);
    bm_set_bit(bm, 2, 0);
    bm_set_bit(bm, 2, 1);
    bm_set_bit(bm, 2, 3);
    bm_set_bit(bm, 3, 0);
    bm_set_bit(bm, 3, 1);
    bm_set_bit(bm, 3, 2);
    bm_set_bit(bm, 4, 0);
    bm_set_bit(bm, 5, 1);
    bm_set_bit(bm, 6, 2);
    bm_set_bit(bm, 7, 3);

    while ((lnc = fgetc(in_fp)) != EOF && (unc = fgetc(in_fp)) != EOF) {
        hs = ham_decode(bm, lnc, &lnm);
        count_stats(hs, &bytes_processed, &corrections, &uncorrected_errors);

        hs = ham_decode(bm, unc, &unm);
        count_stats(hs, &bytes_processed, &corrections, &uncorrected_errors);

        fputc(pack_byte(unm, lnm), out_fp);
    }
    if (verbose) {
        fprintf(out_fp, "Total bytes processed: %d\n", bytes_processed);
        fprintf(out_fp, "Uncorrected errors: %d\n", uncorrected_errors);
        fprintf(out_fp, "Corrected errors: %d\n", corrections);
        fprintf(out_fp, "Error rate: %f\n", (double) uncorrected_errors / bytes_processed);
    }
}
