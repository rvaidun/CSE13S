#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
// Code from assignment PDF
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// Code from assignment PDF for assignment 3
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = malloc(capacity * sizeof(Node));
    }
    return s;
}

// Code from assignment PDF for assignment 3
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        (*s)->items = NULL;
        free(*s);
        *s = NULL;
    }
    return;
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
bool stack_push(Stack *s, Node *n) {
    if (!stack_full(s)) {
        s->items[s->top] = n;
        s->top++;
        return true;
    }
    return false;
}

// Removes an item from the stack and returns the item through the pointer x
bool stack_pop(Stack *s, Node **n) {
    if (!stack_empty(s)) {
        s->top--;
        *n = s->items[s->top];
        s->items[s->top] = 0;
        return true;
    }
    return false;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->capacity; i++) {
        node_print(s->items[i]);
    }
}
