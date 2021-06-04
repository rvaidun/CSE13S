#include "ht.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// Creates a new hash table
// Code from assignment PDF
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

// Deletes the hash table
void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < ht_size((*ht)); i++) {
            ll_delete(&(*ht)->lists[i]);
        }
        free((*ht)->lists);
        (*ht)->lists = NULL;
        free((*ht));
        *ht = NULL;
    }
    return;
}

// Returns the size of the hash table
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Checks if a oldspeak word is in the hash table
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t ind = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[ind] == NULL) {
        return NULL;
    } else {
        return ll_lookup(ht->lists[ind], oldspeak);
    }
}

// Inserts a oldspeak, newspeak pair into the hash table
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t ind = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[ind] == NULL) {
        // If the linked list is not initialized then initialize it
        ht->lists[ind] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[ind], oldspeak, newspeak);
    return;
}

// Counts the number of initialized linked lists
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i]) {
            count++;
        }
    }
    return count;
}

// Prints the hash table
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i]) {
            ll_print(ht->lists[i]);
        }
    }
    return;
}
