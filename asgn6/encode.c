#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // For getopt
#define OPTIONS "hvi:o:"

// Prints the help message
void print_help(void) {
    printf("SYNOPSIS\n"
           "   A Huffman encoder\n"
           "   Compress a file using the Huffman coding algorithm\n"
           "USAGE\n"
           "   ./encode [-h] [-v] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h             Display program help and usage.\n"
           "   -i infile      Input data to compress (default: stdin)\n"
           "   -o outfile     Output of compressed data (default: stdout)\n"
           "   -v             Print compression statistics.\n");

    return;
}

void print_histogram(uint64_t *hist) {
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            printf("character: %c, amount: %" PRIu64 "\n", i, hist[i]);
        }
    }
}

void postorder_traversal(Node *root, uint8_t *arr, uint32_t *i) {
    if (root) {
        postorder_traversal(root->left, arr, i);
        postorder_traversal(root->right, arr, i);
        if (root->left == NULL && root->right == NULL) {
            arr[*i] = 'L';
            *i = *i + 1;
            arr[*i] = root->symbol;
            *i = *i + 1;
        } else {
            arr[*i] = 'I';
            *i = *i + 1;
        }
    }
}
int main(int argc, char **argv) {

    int bytes_read;
    Header h;
    struct stat statbuf;
    uint8_t dump[MAX_TREE_SIZE];
    uint8_t buf[BLOCK];

    uint8_t unique_symbols = 0;
    uint32_t dump_index = 0;
    int infile = 0;
    int outfile = 1;
    bool temp = false;
    bool verbose = false;
    Code table[ALPHABET] = { 0 };

    uint64_t hist[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }
    hist[0]++;
    hist[255]++;

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
        int tempfile = open("encode.temporary", O_CREAT | O_RDWR);

        while ((bytes_read = read_bytes(0, buf, BLOCK)) > 0) {
            write_bytes(tempfile, buf, bytes_read);
        }

        infile = tempfile;
        temp = true;
    }

    lseek(infile, 0, SEEK_SET);
    while ((bytes_read = read_bytes(infile, buf, BLOCK)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            hist[buf[i]]++;
        }
    }

    // print_histogram(hist);
    // Count unique symbols
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            unique_symbols++;
        }
    }

    // Get the stats for the infile and change mode
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);

    // Build root and codes
    Node *root = build_tree(hist);
    // node_print(root);
    // return -1;
    build_codes(root, table);
    // code_print(c);
    // return -1;
    // Build header and write it
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = statbuf.st_size;
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));

    // Post order traversal through the tree to make a tree dump buffer
    postorder_traversal(root, dump, &dump_index);
    write_bytes(outfile, dump, dump_index);

    // Seek back to 0, loop through each byte and write the corresponding code
    lseek(infile, 0, SEEK_SET);
    while ((bytes_read = read_bytes(infile, buf, BLOCK)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            write_code(outfile, &table[buf[i]]);
        }
    }

    // If temp file was created delete the file
    if (verbose) {
        printf("Verbose");
    }
    if (temp) {
        unlink("encode.temporary");
    }
}
