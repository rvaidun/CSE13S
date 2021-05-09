#include "hamming.h"

#include "bm.h"

#include <stdio.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, 4);
    BitMatrix *code = bm_multiply(m, G);
    uint8_t c = bm_to_data(code);
    bm_delete(&m);
    bm_delete(&code);
    return c;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    int8_t table[] = { HAM_CORRECT, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *cm = bm_from_data(code, 8);
    BitMatrix *error_syndrome = bm_multiply(cm, Ht);
    uint8_t es = bm_to_data(error_syndrome);
    if (es == 0) {
        bm_delete(&cm);
        bm_delete(&error_syndrome);
        *msg = code & 0xF;
        return HAM_OK;
    } else if (table[es] == HAM_ERR) {
        bm_delete(&cm);
        bm_delete(&error_syndrome);
        return HAM_ERR;
    }

    if (bm_get_bit(cm, 0, table[es])) {
        bm_clr_bit(cm, 0, table[es]);
    } else {
        bm_set_bit(cm, 0, table[es]);
    }

    uint8_t correct_code = bm_to_data(cm);
    *msg = correct_code & 0xF;
    bm_delete(&cm);
    bm_delete(&error_syndrome);
    return HAM_CORRECT;
}
