
#include "bm.h"

#include "bv.h"
#include "bvbyte.h"

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
    bv_get_bit(m->vector, r * m->cols + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    uint8_t bit;
    if (bm) {
        bm->rows = 1;
        bm->cols = length;
        bm->vector = bv_create(length);
        bv_set_byte(bm, byte, 0);
        // for (uint32_t i = 0; i < length; i++) {
        //     bit = (byte >> i) & 1;
        //     if (bit) {
        //         bv_set_bit(bm->vector, i);
        //     }
        // }
    }
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
        for (uint32_t i = 0; i < A->cols; i++) {
            for (uint32_t j = 0; j < A->rows; j++) {
                for (uint32_t k = 0; k < B->cols; k++) {
                    if (bm_get_bit(A, i, k) ^ bm_get_bit(B, k, j)) {
                        bm_set_bit(bm, i, j);
                    }
                }
            }
        }
    }
    return bm;
}

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
}
