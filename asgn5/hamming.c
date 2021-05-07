#include "hamming.h"

#include "bm.h"

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, 4);
    BitMatrix *code = bm_multiply(m, G);
    return bm_to_data(code);
}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    uint8_t table = { HAM_CORRECT, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *bm = bm_from_data(code, 8);
    BitMatrix *error_syndrome = bm_multiply(bm, Ht);
    uint8_t es = bm_to_data(error_syndrome);
    if (es == 0) {
        *msg = bm_to_data(bm);
        return HAM_OK;
    } else if (es == HAM_ERR) {
        *msg = bm_to_data(bm);
        return HAM_ERR;
    }

    if (bm_get_bit(bm, 0, es)) {
        bm_clr_bit(bm, 0, es);
    } else {
        bm_set_bit(bm, 0, es);
    }
    return HAM_CORRECT;
}
