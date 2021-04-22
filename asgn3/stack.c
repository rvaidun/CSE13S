#include "stack.h"

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
    for (int i = 0; i < s->capacity; i++) {
        printf("%lld", s->items[i]);
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
    return true;
}

// Removes an item from the stack
bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top];
    s->items[s->top] = 0;
    s->top--;
    return true;
}

int main(void) {
    int64_t temp;
    bool x;
    Stack *s = stack_create(3);
    stack_print(s);
    x = stack_pop(s, &temp);
    printf("success -> %d\ntemp -> %lld", x, temp);
    x = stack_push(s, 5);
    stack_print(s);
    printf("success -> %d\n", x);
    stack_push(s, 4);
    stack_print(s);
    stack_push(s, 4);
    stack_print(s);
    x = stack_push(s, 4);
    stack_print(s);
    printf("success -> %d\n", x);
}
