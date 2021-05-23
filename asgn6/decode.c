#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h> // For open, read and write
#include <inttypes.h>
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
    uint64_t bw = 0;
    Header h;
    Node *root_node;
    Node *node;
    struct stat instatbuf;
    uint8_t buf[BLOCK];
    uint8_t bit;
    uint32_t buf_index = 0;
    int infile = 0;
    int outfile = 1;
    int opt = 0;
    bool verbose = false;

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
        case 'v': verbose = true; break;
        default: print_help(); return -1;
        }
    }
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));

    if (h.magic != MAGIC) {
        fprintf(stderr, "Error: unable to read header.\n");
        return -1;
    }

    fstat(infile, &instatbuf);
    fchmod(outfile, h.permissions);

    uint8_t dump[h.tree_size];
    read_bytes(infile, dump, h.tree_size);
    root_node = rebuild_tree(h.tree_size, dump);
    node = root_node;
    while (bw < h.file_size && read_bit(infile, &bit)) {
        node = bit ? node->right : node->left;

        if (node->left == NULL && node->right == NULL) {
            buf[buf_index++] = node->symbol;
            bw++;
            node = root_node;

            if (buf_index == BLOCK) {
                write_bytes(outfile, buf, BLOCK);
                buf_index = 0;
            }
            continue;
        }
    }
    write_bytes(outfile, buf, buf_index);

    if (verbose) {
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", instatbuf.st_size);
        fprintf(stderr, "Decompressed file size: %" PRIu64 " bytes\n", bytes_read);
        fprintf(stderr, "Space saving: %.2f%%\n",
            100 * (1 - ((double) instatbuf.st_size / bytes_read)));
    }
}
