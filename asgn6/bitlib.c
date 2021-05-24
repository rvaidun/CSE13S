#include <inttypes.h>

// Bit library

// Given a bit vector and bit index set the particular bit
void set_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] |= (1 << bitpos);
    return;
}

// Clear a bit from the bit vector
void clr_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    v[bytepos] &= ~(1 << bitpos);
    return;
}

// Return value of bit in the bit vector
uint8_t get_bit(uint8_t *v, uint32_t i) {
    uint32_t bytepos = i / 8;
    uint32_t bitpos = i % 8;
    return (v[bytepos] >> bitpos) & 1;
}
