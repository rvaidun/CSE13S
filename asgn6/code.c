#include "code.h"

#include <stdio.h>
#include <stdlib.h>
Code code_init(void) {
    static Code c = { 0, { 0 } };
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return c->top == 0;
}

bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top == MAX_CODE_SIZE) {
        return false;
    }
    c->bits[c->top] = bit;
    c->top++;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c->top == 0) {
        return false;
    }
    c->top--;
    *bit = c->bits[c->top];
    c->bits[c->top] = 0;
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%d ", c->bits[i]);
    }
    printf("\n");
}
