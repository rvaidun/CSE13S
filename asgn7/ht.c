#include "ht.h"

#include "speck.h"

#include <stdlib.h>
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht) {
        free((*ht)->lists);
        (*ht)->lists = NULL;
        free((*ht));
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    return ll_lookup(ht->lists[hash(ht->salt, oldspeak)], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    ll_insert(ht->lists[hash(ht->salt, oldspeak)], oldspeak, newspeak);
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (int i = 0; i < ht->size; i++) {
        if (ht->lists[i]) {
            count++;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->lists[i]) {
            ll_print(ht->lists[i]);
        }
    }
    return;
}
