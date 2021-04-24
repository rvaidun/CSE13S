#include "stack.h"

#include "quick.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
// Code from assignment PDF
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// Code from assignment PDF
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Code from assignment PDF
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Prints a stack
void stack_print(Stack *s) {
    printf("{");
    for (uint32_t i = 0; i < s->capacity; i++) {
        printf("%" PRId64, s->items[i]);
        printf(i != s->capacity - 1 ? ", " : "");
    }
    printf("}\n");
}

// Returns true if stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// Returns true if stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

// Returns the number of items in the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Adds an item to the stack
bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;

    // On each push check if current stack size greater than current stack size
    if (max_stack_size < stack_size(s)) {
        max_stack_size = stack_size(s);
    }

    return true;
}

// Removes an item from the stack
bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    s->items[s->top] = 0;

    return true;
}
