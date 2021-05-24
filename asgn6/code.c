#include "code.h"

#include "bitlib.h"

#include <stdio.h>
#include <stdlib.h>

// Call this function to create a new code
Code code_init(void) {
    Code c = { 0, { 0 } };
    return c;
}

// Returns the size of code
uint32_t code_size(Code *c) {
    return c->top;
}

// Returns if the code is empty
bool code_empty(Code *c) {
    return c->top == 0;
}

// Return if the code is full
bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE) {
        return true;
    }
    return false;
}

// Pushes a bit onto the code
bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top == MAX_CODE_SIZE) {
        return false;
    }
    if (bit) {
        set_bit(c->bits, c->top++);
    } else {
        clr_bit(c->bits, c->top++);
    }
    return true;
}

// Pops a bit from the code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c->top == 0) {
        return false;
    }
    *bit = get_bit(c->bits, --c->top);
    return true;
}

// Debug function to print the code
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%d ", c->bits[i]);
    }
    printf("\n");
}
