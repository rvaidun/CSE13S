#include "hamming.h"

#include "bm.h"

#include <stdio.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, 4);
    BitMatrix *code = bm_multiply(m, G);
    return bm_to_data(code);
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    int8_t table[] = { HAM_CORRECT, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *bm = bm_from_data(code, 8);
    BitMatrix *error_syndrome = bm_multiply(bm, Ht);
    uint8_t es = bm_to_data(error_syndrome);
    *msg = code & 0xF;
    if (es == 0) {
        return HAM_OK;
    } else if (table[es] == HAM_ERR) {
        return HAM_ERR;
    }

    if (bm_get_bit(bm, 0, table[es])) {
        bm_clr_bit(bm, 0, table[es]);
    } else {
        bm_set_bit(bm, 0, table[es]);
    }
    *msg = code & 0xF;
    return HAM_CORRECT;
}
