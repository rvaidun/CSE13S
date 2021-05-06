#include "bv.h"
#include <stdint.h>

uint8_t bv_get_byte(BitVector *v, uint32_t i);

void bv_set_bytes(BitVector *v, uint8_t *byte, uint32_t nbytes);
