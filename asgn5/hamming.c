#include "hamming.h"

#include "bm.h"

#include <stdio.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, 4); // m is the message that we need encoded
    BitMatrix *code = bm_multiply(m, G); // create the code by multiplying the matrices
    uint8_t c = bm_to_data(code); // store the code as a number

    // Free up space that we allocated
    bm_delete(&m);
    bm_delete(&code);
    return c;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    int8_t bit_table[] = { HAM_CORRECT, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR,
        2, HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *cm = bm_from_data(code, 8); // cm is the code message as a bit matrix.
    BitMatrix *error_syndrome = bm_multiply(cm, Ht);
    uint8_t es = bm_to_data(error_syndrome); // es as an integer

    if (bit_table[es] == HAM_OK) {
        // Free up space
        bm_delete(&cm);
        bm_delete(&error_syndrome);
        *msg = code & 0xF; // Set a new value for the msg
        return HAM_OK;
    } else if (bit_table[es] == HAM_ERR) {
        bm_delete(&cm);
        bm_delete(&error_syndrome);
        return HAM_ERR;
    }

    if (bm_get_bit(cm, 0, bit_table[es])) { // Flip the bit in bit_table[es]
        bm_clr_bit(cm, 0, bit_table[es]);
    } else {
        bm_set_bit(cm, 0, bit_table[es]);
    }

    // Get the corrected code as an integer and send just the data nibble
    uint8_t correct_code = bm_to_data(cm);
    *msg = correct_code & 0xF;
    bm_delete(&cm);
    bm_delete(&error_syndrome);
    return HAM_CORRECT;
}
