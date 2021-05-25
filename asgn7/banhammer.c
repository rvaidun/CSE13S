// [A-Za-z0-9\_]?[A-Za-z0-9\_\-\']*[A-Za-z0-9\_]{1}
#include "bf.h"
#include "ht.h"
#include "llnode.h"
#include "messages.h"
#include "node.h"

#include <math.h>
#include <parser.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For getopt
#define OPTIONS "hmst:f:"
#define WORD    "[A-Za-z0-9\_]?[A-Za-z0-9\_\-\']*[A-Za-z0-9\_]{1}"

void print_help(void) {
    printf("SYNOPSIS\n"
           "   A word filtering program for the GPRSC.\n"
           "   Filters out and reports bad words parsed from stdin.\n"
           "USAGE\n"
           "   ./banhammer [-hsm] [-t size] [-f size]\n\n"
           "OPTIONS\n"
           "   -h             Display program help and usage.\n"
           "   -s           Print program statistics.\n"
           "   -m           Enable move-to-front rule.\n"
           "   -t size      Specify hash table size (default: 10000).\n"
           "   -f size      Specify Bloom filter size (default: 2^20).\n");
    return;
}
int main(int argc, char **argv) {
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex. \n");
        return 1;
    }
    LinkedList *badspeakwords = ll_create(false);
    LinkedList *translations = ll_create(false);
    uint32_t badspeaklength;
    uint32_t translationslength;
    BloomFilter *bf;
    HashTable *ht;
    char *badspeak;
    char *newspeak;
    char *oldspeak;
    char *word;
    Node *n;
    FILE *bspkf = fopen("badspeak.txt", "r");
    FILE *nspkf = fopen("newspeak.txt", "r");
    bool stats = false;
    bool mtf = false;
    uint32_t bf_size = (uint32_t) pow(2, 20);
    uint32_t ht_size = 10000;
    int temp;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        case 's': stats = true; break;
        case 'm': mtf = true; break;
        case 't': ht_size = optarg; break;
        case 'f': bf_size = optarg; break;
        default: print_help(); break;
        }
    }

    bf = bf_create(bf_size);
    ht = ht_create(ht_size, mtf);

    while ((temp = fscanf(bspkf, "%s", &badspeak)) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(bf, badspeak, NULL);
    }
    while ((temp = fscanf(nspkf, "%s %s", &oldspeak, &newspeak)) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(bf, oldspeak, newspeak);
    }
    while ((word = next_word(stdin, &re)) != NULL) {
        if (bf_probe(bf, oldspeak)) {
            n = ht_lookup(ht, oldspeak);
            if (n != NULL) {

                if (n->newspeak && n->oldspeak) {
                    ll_insert_from_node(translations, n);
                } else if (n->oldspeak) {
                    ll_insert_from_node(badspeakwords, n);
                }
            }
        }
    }

    badspeaklength = ll_length(badspeakwords);
    translationslength = ll_length(translations);

    if (badspeaklength > 0 && translations > 0) {
        fprintf(stdout, "%s", mixspeak_message);
        ll_print(badspeakwords);
        ll_print(translations);
    } else if (badspeaklength > 0) {
        fprintf(stdout, "%s", badspeak_message);
        ll_print(badspeakwords);
    } else if (translations > 0) {
        fprintf(stdout, "%s", goodspeak_message);
        ll_print(translations);
    }
}
