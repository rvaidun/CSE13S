#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // To set file permissions
#include <unistd.h> // For getopt
#define OPTIONS         "hvi:o:"
#define STATS_INDEX     4
#define STATS_TOTAL     0
#define STATS_CORRECTED 3 //HAM_CORRECT + STAT_INDEX
#define STATS_ERROR     2 //HAM_ERR + STAT_INDEX

// Prints the help message
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
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    // Set defaults
    bool verbose = false;
    FILE *in_fp = stdin;
    FILE *out_fp = stdout;
    struct stat statbuf;

    // lnc and unc are lower nibble code and upper nibble code
    int lnc;
    int unc;
    // lnm and unm are lower nibble message and upper nubble message
    uint8_t lnm = 0;
    uint8_t unm = 0;
    HAM_STATUS hs;
    uint8_t decode_table[256];
    int8_t status_table[256];
    uint32_t stats[STATS_INDEX] = { 0, 0, 0, 0 };

    int opt = 0;
    // Parse command line arguments
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

    // Create the decoder matrix based on the matrix from the assignment pdf and set the proper bits
    BitMatrix *Ht = bm_create(8, 4);
    bm_set_bit(Ht, 0, 1);
    bm_set_bit(Ht, 0, 2);
    bm_set_bit(Ht, 0, 3);
    bm_set_bit(Ht, 1, 0);
    bm_set_bit(Ht, 1, 2);
    bm_set_bit(Ht, 1, 3);
    bm_set_bit(Ht, 2, 0);
    bm_set_bit(Ht, 2, 1);
    bm_set_bit(Ht, 2, 3);
    bm_set_bit(Ht, 3, 0);
    bm_set_bit(Ht, 3, 1);
    bm_set_bit(Ht, 3, 2);
    bm_set_bit(Ht, 4, 0);
    bm_set_bit(Ht, 5, 1);
    bm_set_bit(Ht, 6, 2);
    bm_set_bit(Ht, 7, 3);

    // Create a lookup table for the codes and the status
    for (int i = 0; i < 256; i++) {
        hs = ham_decode(Ht, i, &lnm);
        status_table[i] = hs;
        decode_table[i] = lnm;
    }
    lnm = 0; // reset lnm to 0 since the for loop above used lnm
    while ((lnc = fgetc(in_fp)) != EOF && (unc = fgetc(in_fp)) != EOF) {

        stats[STATS_TOTAL] += 2;

        // Only set lnm if we get the status of ham_correct or ham_ok
        if (status_table[lnc] == HAM_CORRECT || status_table[lnc] == HAM_OK) {
            lnm = decode_table[lnc];
        }
        // Count stats
        stats[status_table[lnc] + STATS_INDEX]++;

        if (status_table[unc] == HAM_CORRECT || status_table[unc] == HAM_OK) {
            unm = decode_table[unc];
        }
        stats[status_table[unc] + STATS_INDEX]++;

        fputc(pack_byte(unm, lnm), out_fp); // Write bytes back
    }
    if (verbose) {
        fprintf(stderr, "Total bytes processed: %d\n", stats[STATS_TOTAL]);
        fprintf(stderr, "Uncorrected errors: %d\n", stats[STATS_ERROR]);
        fprintf(stderr, "Corrected errors: %d\n", stats[STATS_CORRECTED]);
        fprintf(stderr, "Error rate: %f\n", (double) stats[STATS_ERROR] / stats[STATS_TOTAL]);
    }
    bm_delete(&Ht);
    fclose(in_fp);
    fclose(out_fp);
}
