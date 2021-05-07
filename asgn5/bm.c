
#include "bm.h"

#include "bv.h"
#include "bvbyte.h"

#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm) {
        bm->rows = rows;
        bm->cols = cols;
        bm->vector = bv_create(rows * cols);
    }
    return bm;
}

void bm_delete(BitMatrix **m) {
    if (*m) {
        bv_delete(&(*m)->vector);
        free(*m);
        *m = NULL;
    }
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c);
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * m->cols + c);
}
void bm_set_vector(BitVector *bv, uint8_t byte, uint32_t l) {
    uint8_t bit;
    for (uint32_t i = 0; i < l; i++) {
        bit = (byte >> i) & 1;
        if (bit) {
            bv_set_bit(bv, i);
        }
    }
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm) {
        bm->rows = 1;
        bm->cols = length;
        bm->vector = bv_create(length);
        bm_set_vector(bm->vector, byte, length);
        // for (uint32_t i = 0; i < length; i++) {
        //     bit = (byte >> i) & 1;
        //     if (bit) {
        //         bv_set_bit(bm->vector, i);
        //     }
        // }
    }
    return bm;
}

BitMatrix *bm_from_data_array(uint8_t *bytes, uint32_t nbytes) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (!bm)
        return NULL;
    bm->rows = nbytes;
    bm->cols = 8;
    bm->vector = bv_create(nbytes * 8);
    bv_set_bytes(bm->vector, bytes, nbytes);
    return bm;
    // for (uint32_t i = 0; i < nbytes; i++) {
    //     bit = (byte >> i) & 1;
    //     if (bit) {
    //         bv_set_bit(bm->vector, i);
    //     }
    // }
}

uint8_t bm_to_data(BitMatrix *m) {
    return bv_get_byte(m->vector, 0);
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm) {
        bm->rows = A->rows;
        bm->cols = B->cols;
        bm->vector = bv_create(bm->rows * bm->cols);
        for (uint32_t i = 0; i < A->rows; i++) {
            for (uint32_t j = 0; j < B->cols; j++) {
                uint8_t temp = 0;
                for (uint32_t k = 0; k < B->cols; k++) {
                    uint8_t bit1 = bm_get_bit(A, i, k);
                    uint8_t bit2 = bm_get_bit(B, k, j);
                    temp = temp ^ (bit1 & bit2);
                }
                if (temp) {
                    bm_set_bit(bm, i, j);
                }
            }
        }
    }
    return bm;
}

void bm_print(BitMatrix *m) {
    for (uint32_t r = 0; r < m->rows; r++) {
        for (uint32_t c = 0; c < m->cols; c++) {
            printf("%d ", bm_get_bit(m, r, c));
        }
        printf("\n");
    }
}

// int main(void) {

//     uint8_t arr[] = { 0xe1, 0xd2, 0xb4, 0x78 };
//     BitMatrix *bm = bm_from_data_array(arr, 4);
//     BitMatrix *c = bm_from_data(0xc, 4);
//     BitMatrix *m;
//     bm_print(bm);
//     bm_print(c);
//     m = bm_multiply(c, bm);
//     printf("\n");
//     bm_print(m);
// }
