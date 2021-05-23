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
    Node *root_node;
    Node *node;
    struct stat statbuf;
    uint8_t buf[BLOCK];
    uint8_t bit;
    int bytes_read;
    uint32_t buf_index = 0;
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

    fstat(infile, &statbuf);
    // If the infile is stdio write to a temporary file and then so we can seek
    if (infile == 0) {
        int tempfile = open("decode.temporary", O_CREAT | O_RDWR);

        while ((bytes_read = read_bytes(0, buf, BLOCK)) > 0) {
            write_bytes(tempfile, buf, bytes_read);
        }

        infile = tempfile;
        temp = true;
    }
    lseek(infile, 0, SEEK_SET);
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    printf("%x\n", h.magic);

    if (h.magic != MAGIC) {
        fprintf(stderr, "Error: unable to read header.\n");
        return -1;
    }

    fchmod(outfile, h.permissions);
    uint8_t dump[h.tree_size];
    read_bytes(infile, dump, h.tree_size);
    root_node = rebuild_tree(h.tree_size, dump);

    node = root_node;
    while (read_bit(infile, &bit)) {
        if (node->left == NULL && node->right == NULL) {
            buf[buf_index] = node->symbol;

            buf_index = (buf_index + 1) % (BLOCK);
            if (buf_index == 0) {
                write_bytes(outfile, buf, 1);
            }
        }
        if (bit) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    write_bytes(outfile, buf, buf_index);

    if (temp) {
        unlink("decode.temporary");
    }
    return 0;
}
