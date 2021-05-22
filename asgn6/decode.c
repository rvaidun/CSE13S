#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h> // For open, read and write
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h> // For open read, and write
#include <unistd.h> // For getopt
#define OPTIONS "hvi:o:"

void print_help(void) {
    printf("SYNOPSIS\n"
           "   A Huffman encoder\n"
           "   Decompresses a file using the Huffman coding algorithm.\n"
           "USAGE\n"
           "   ./decode [-h] [-v] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h             Display program help and usage.\n"
           "   -i infile      Input data to compress (default: stdin)\n"
           "   -o outfile     Output of compressed data (default: stdout)\n"
           "   -v             Print compression statistics.\n");

    return;
}

int main(int argc, char **argv) {
    Header h;
    // struct stat statbuf;
    uint8_t buf[BLOCK];
    int bytes_read;
    int infile = 0;
    int outfile = 1;
    bool temp = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                printf("Error opening file\n");
                return -1;
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT);
            if (outfile == -1) {
                printf("Error opening file\n");
                return -1;
            }
            break;
        default: break;
        }
    }

    // If the infile is stdio write to a temporary file and then so we can seek
    if (infile == 0) {
        int tempfile = open("decode.temporary", O_CREAT | O_RDWR);

        while ((bytes_read = read_bytes(0, buf, BLOCK)) > 0) {
            write_bytes(tempfile, buf, bytes_read);
        }

        infile = tempfile;
        temp = true;
    }

    // write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    printf("%x\n", h.magic);
    return -1;
    if (temp) {
        unlink("decode.temporary");
    }
}
