#include <inttypes.h>

void set_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] |= (1 << bitpos);
    return;
}

void clr_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] &= ~(1 << bitpos);
    return;
}

uint8_t get_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    return (v[bytepos] >> bitpos) & 1;
}
