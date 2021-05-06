#include "bv.h"

#include <stdio.h>
#include <stdlib.h>
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->length = ((length - 1) / 8) + 1;
        bv->vector = (uint8_t *) calloc(bv->length, sizeof(uint8_t));
    }
    return bv;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v->vector[bytepos] |= (1 << bitpos);
    return;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v->vector[bytepos] &= ~(1 << bitpos);
    return;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    return (v->vector[bytepos] >> bitpos) & 1;
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    uint8_t b = bv_get_bit(v, i);
    v->vector[bytepos] = (v->vector[bytepos] & (~(1 << bitpos))) | ((b ^ bit) << bitpos);
}

uint8_t bv_get_byte(BitVector *v, uint32_t i) {
    return v->vector[i];
}

void bv_set_bytes(BitVector *v, uint8_t *byte, uint32_t nbytes) {
    for (uint32_t b = 0; b < nbytes; b++) {
        v->vector[b] = byte[b];
    }
}

void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < v->length; i++) {
        printf("bv[%d]=%d \n", i, v->vector[i]);
    }
    printf("\n");
}

// int main(void) {
//     BitVector *bv = bv_create(4);
//     bv_set_bit(bv, 3);
//     bv_set_bit(bv, 2);
//     for (int i = 0; i < 4; i++) {
//         printf("Value at %d - %d\n", i, bv_get_bit(bv, i));
//     }
// }
