#include "hamming.h"

#include "bm.h"
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *bm = bm_from_data(msg, 4);
}
