#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdint.h>
#include <stdio.h>
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// Creates a Bloom Filter. Code was taken from Assignment PDF
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm 's Fairy
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

// Delete a bloom filter and free up any space
void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

// Returns the size of the bloom filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Insers a new word into the filter.
// Hash each of the salts and set the hashed index in the filter
void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak));
}

// Similar to insert but say if all three hashed indices are set
// If they are all set the word was most likely added to the filter
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    if (bv_get_bit(bf->filter, hash(bf->primary, oldspeak))
        && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak))
        && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak))) {
        return true;
    }
    return false;
}

// Count the number of set bits
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) { // Loop through the filter
        if (bv_get_bit(bf->filter, i)) {
            count++;
        }
    }
    return count;
}

// Print a bloom filter
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
