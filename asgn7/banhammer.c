// 'look .nr x0 n(.l
#include "bf.h"
#include "ht.h"
#include "llnode.h"
#include "messages.h"
#include "node.h"
#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For getopt
#define OPTIONS "hmst:f:"
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"

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
        fprintf(stderr, "regex broken\n");
        return 1;
    }
    LinkedList *badspeakwords = ll_create(false);
    LinkedList *translations = ll_create(false);
    uint32_t badspeaklength;
    uint32_t translationslength;
    BloomFilter *bf;
    HashTable *ht;
    char buffer[1024];
    char buffer2[1024];
    char *word;
    char *first_invalid;
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

        case 't':
            ht_size = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                return -1;
            }
            break;

        case 'f':
            bf_size = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                return -1;
            }
            break;
        default: print_help(); break;
        }
    }

    // Initialize bloom filter and hash table
    bf = bf_create(bf_size);
    ht = ht_create(ht_size, mtf);
    while ((temp = fscanf(bspkf, "%s", buffer)) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }
    while ((temp = fscanf(nspkf, "%s %s", buffer, buffer2)) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, buffer2);
    }

    while ((word = next_word(stdin, &re)) != NULL) {
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        if (strcmp(word, "fo") == 0) {
            fprintf(stderr, "found fo\n");
        }
        if (bf_probe(bf, word)) {
            n = ht_lookup(ht, word);
            if (n != NULL) {
                if (n->newspeak && n->oldspeak) {
                    ll_insert(translations, n->oldspeak, n->newspeak);
                } else if (n->oldspeak) {
                    ll_insert(badspeakwords, n->oldspeak, NULL);
                }
            }
        }
    }
    badspeaklength = ll_length(badspeakwords);
    translationslength = ll_length(translations);
    if (badspeaklength > 0 && translationslength > 0) {
        fprintf(stdout, "%s", mixspeak_message);
        ll_print(badspeakwords);
        ll_print(translations);
    } else if (badspeaklength > 0) {
        fprintf(stdout, "%s", badspeak_message);
        ll_print(badspeakwords);
    } else if (translationslength > 0) {
        fprintf(stdout, "%s", goodspeak_message);
        ll_print(translations);
    }
}
