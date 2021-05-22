#define OPTIONS "h"
#include "defines.h"
#include "io.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // For getopt
// Prints the help message
void print_help(void) {
    printf("Help");
    return;
}

int main(int argc, char **argv) {
    int opt = 0;
    uint8_t byte = 0;
    uint8_t bit;
    uint64_t hist[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        }
    }
    int infile = open("test.txt", O_RDONLY);
    int c = 0;
    while (read_bit(infile, &bit)) {
        printf("%d", bit);
        if (bit == 1) {
            byte |= (1 << c); // set the bit
        } else {
            byte &= ~(1 << c); // clear the bit
        }
        c++;

        if (c % 8 == 0) {
            hist[byte]++;
            printf("\n");
        }
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            printf("Index in histogram - %d\n", i);
            printf("%c, %llu\n", i, hist[i]);
        }
    }
}
