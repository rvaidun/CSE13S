
#include "bm.h"

#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Creates a bit matrix with given rows and columns
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm) {
        bm->rows = rows;
        bm->cols = cols;
        bm->vector = bv_create(rows * cols / 8);
    }
    return bm;
}

// Deletes a bit matrix and frees any space that was allocated for the matrix
void bm_delete(BitMatrix **m) {
    if (*m) {
        bv_delete(&(*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}

// returns the amount of rows in the bit matrix
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

// returns the number of columns in the bit matrix
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// sets a bit in the bit matrix
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c);
    return;
}

// Clears a bit in the bit matrix
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c);
    return;
}

// Gets a bit in the bit matrix
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * m->cols + c);
}

// given some data stored in a uint8_t create a bit matrix
// with the dimensions 1xlength
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    uint8_t bit;
    if (bm) {
        bm->rows = 1;
        bm->cols = length;
        bm->vector = bv_create(1);
        for (uint32_t i = 0; i < length; i++) {
            bit = (byte >> i) & 1;
            if (bit) {
                bv_set_bit(bm->vector, i);
            }
        }
    }
    return bm;
}

// Store the first row of the bit matrix as an integer
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t byte = 0;
    for (uint32_t i = 0; i < m->cols; i++) {
        if (bm_get_bit(m, 0, i)) {
            byte |= 1 << i;
        }
    }
    return byte;
}

// Multiply two bit matrices.
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm) {
        bm->rows = A->rows;
        bm->cols = B->cols;
        bm->vector = bv_create(bm->rows * bm->cols);
        for (uint32_t i = 0; i < A->rows; i++) {
            for (uint32_t j = 0; j < B->cols; j++) {
                uint8_t temp = 0;
                for (uint32_t k = 0; k < A->cols; k++) {
                    uint8_t bit1 = bm_get_bit(A, i, k);
                    uint8_t bit2 = bm_get_bit(B, k, j);
                    temp ^= (bit1 & bit2);
                }
                if (temp) {
                    bm_set_bit(bm, i, j);
                }
            }
        }
    }
    return bm;
}

// Debugger function to print bit matrix
void bm_print(BitMatrix *m) {
    for (uint32_t r = 0; r < m->rows; r++) {
        for (uint32_t c = 0; c < m->cols; c++) {
            printf("%d ", bm_get_bit(m, r, c));
        }
        printf("\n");
    }
    return;
}
