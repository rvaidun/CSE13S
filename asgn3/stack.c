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

// bool stack_empty(Stack *s) {
//     for
//         int stac return true;
// }

// Prints a stack
void stack_print(Stack *s) {
    printf("{");
    for (int i = 0; i < s->capacity; i++) {
        printf("%lld", s->items[i]);
        printf(i != s->capacity - 1 ? ", " : "");
    }
    printf("}\n");
}
int main(void) {
    Stack *s = stack_create(3);
    stack_print(s);
    // bool empty = stack_empty(s);
    // printf("%d\n", empty);
}
