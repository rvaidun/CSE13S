// 'look .nr x0 n(.l
#include "bf.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"

#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For getopt

#define OPTIONS "hmst:f:"
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*" // Regex string
// Global number of seeks and links
uint64_t seeks = 0;
uint64_t links = 0;

// Helper function to print help
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

// Main function
int main(int argc, char **argv) {
    regex_t re;

    // Parse regex
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "regex broken\n");
        return 1;
    }

    // Open badspeak.txt and newspeak.txt from CWD
    FILE *bspkf = fopen("badspeak.txt", "r");
    if (!bspkf) {
        fprintf(
            stderr, "Failed to open badspeak.txt. File needs to be in current working directory\n");
    }

    FILE *nspkf = fopen("newspeak.txt", "r");
    if (!nspkf) {
        fprintf(
            stderr, "Failed to open newspeak.txt. File needs to be in current working directory");
    }

    // Initialize all variables
    uint32_t badspeaklength;
    uint32_t translationslength;
    BloomFilter *bf;
    HashTable *ht;
    char buffer[1024];
    char buffer2[1024];
    char *word;
    char *first_invalid;
    Node *n;
    int temp;

    bool stats = false;
    bool mtf = false;
    uint32_t size_bf = (uint32_t) pow(2, 20);
    uint32_t size_ht = 10000;
    int opt = 0;

    // Switch case to parse command line options with getopt
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        case 's': stats = true; break;
        case 'm': mtf = true; break;

        case 't':
            size_ht = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                fprintf(stderr, "Invalid hash table size\n");
                return -1;
            }
            break;

        case 'f':
            size_bf = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                fprintf(stderr, "Invalid Bloom filter size\n");
                return -1;
            }
            break;
        default: print_help(); break;
        }
    }

    // Create linkedlists to the badspeak words and the translations from stdin
    LinkedList *badspeakwords = ll_create(mtf);
    LinkedList *translations = ll_create(mtf);

    // Initialize bloom filter and hash table
    bf = bf_create(size_bf);
    ht = ht_create(size_ht, mtf);

    // For each word in badspeak.txt add the word to the bloom filter and the hashtable
    while ((temp = fscanf(bspkf, "%s", buffer)) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }

    // For each pair of words in newspeak.txt add the oldspeak to the bloom filter and the pair to the hashtable
    while ((temp = fscanf(nspkf, "%s %s", buffer, buffer2)) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, buffer2);
    }

    // For every word from stdin
    while ((word = next_word(stdin, &re)) != NULL) {
        for (int i = 0; word[i]; i++) {
            // Convert to lowercase since newspeak and oldspeak are in lowercase
            word[i] = tolower(word[i]);
        }
        // If the probe is successful we should check if it is in the hash table
        if (bf_probe(bf, word)) {
            n = ht_lookup(ht, word);
            if (n != NULL) {
                // If word is in the hashtable check if there is a corresponding translation and insert into the respective linkedlist
                if (n->newspeak && n->oldspeak) {
                    ll_insert(translations, n->oldspeak, n->newspeak);
                } else if (n->oldspeak) {
                    ll_insert(badspeakwords, n->oldspeak, NULL);
                }
            }
        }
    }

    if (!stats) {
        // If stats is disabled print the message
        badspeaklength = ll_length(badspeakwords);
        translationslength = ll_length(translations);
        if (badspeaklength > 0 && translationslength > 0) {
            // If there are badspeak words and translation words
            fprintf(stdout, "%s", mixspeak_message);
            ll_print(badspeakwords);
            ll_print(translations);
        } else if (badspeaklength > 0) {
            // If there are only bad speak words
            fprintf(stdout, "%s", badspeak_message);
            ll_print(badspeakwords);
        } else if (translationslength > 0) {
            // If there are only translation words
            fprintf(stdout, "%s", goodspeak_message);
            ll_print(translations);
        }

    } else {
        // print stats
        fprintf(stdout, "Seeks: %" PRIu64 "\n", seeks);
        fprintf(stdout, "Average seek length: %f\n", ((double) links / seeks));
        fprintf(stdout, "Hash table load: %f%%\n", 100 * ((double) ht_count(ht) / ht_size(ht)));
        fprintf(stdout, "Bloom filter load: %f%%\n", 100 * ((double) bf_count(bf) / bf_size(bf)));
    }

    // Delete and free up memory so there are no memory leaks
    fclose(bspkf);
    fclose(nspkf);
    ll_delete(&badspeakwords);
    ll_delete(&translations);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
