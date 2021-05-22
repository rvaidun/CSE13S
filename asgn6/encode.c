
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // For getopt

#define OPTIONS "h"

// Prints the help message
void print_help(void) {
    printf("Help");
    return;
}

void print_histogram(uint64_t *hist) {
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            printf("character: %c, amount: %llu\n", i, hist[i]);
        }
    }
}

void postorder_traversal(Node *root, uint8_t *arr, uint32_t *i) {
    if (root) {
        postorder_traversal(root->left, arr, i);
        postorder_traversal(root->right, arr, i);
        if (root->left == NULL && root->right == NULL) {
            arr[*i++] = 'L';
            arr[*i++] = root->symbol;
        } else {
            arr[*i++] = 'I';
        }
    }
}
int main(int argc, char **argv) {
    int opt = 0;
    uint8_t byte = 0;
    uint8_t bit;
    uint8_t unique_symbols = 0;
    uint64_t hist[ALPHABET];
    uint8_t dump[MAX_TREE_SIZE];
    uint32_t dump_index = 0;
    Header h;
    Code table[ALPHABET] = { 0 };
    struct stat statbuf;
    int infile = open("test.txt", O_RDONLY);
    int outfile = open("testout.txt", O_WRONLY);
    fstat(infile, &statbuf);
    uint8_t buf[statbuf.st_size];

    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }
    hist[0]++;
    hist[255]++;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        }
    }

    read_bytes(infile, buf, statbuf.st_size);
    for (int i = 0; i < statbuf.st_size; i++) {
        hist[buf[i]]++;
    }
    print_histogram(hist);

    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            unique_symbols++;
        }
    }
    fchmod(outfile, &statbuf.st_mode);

    Node *root = build_tree(hist);
    build_codes(root, table);

    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = statbuf.st_size;

    write_bytes(outfile, (uint8_t *) &h, sizeof(h));
    postorder_traversal(root, dump, &dump_index);
    write_bytes(outfile, dump, dump_index);
    // write_code(outfile, )
}
