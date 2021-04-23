#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

extern uint32_t moves, compares;

int64_t partition(uint32_t *arr, int64_t lo, int64_t hi) {
    int64_t pivot, i, j, temp;
    pivot = arr[lo + ((hi - lo) / 2)];
    i = lo - 1;
    j = hi + 1;
    while (i < j) {
        do {
            i++;
            compares++;
        } while (arr[i] < pivot);

        do {
            j -= 1;
            compares++;
        } while (arr[j] > pivot);

        if (i < j) {
            moves += 3;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    return j;
}

// Quicksort with stack
void quick_sort_stack(uint32_t *arr, uint32_t n) {
    moves = 0;
    compares = 0;
    max_stack_size = 0;
    int64_t p, lo, hi;
    lo = 0;
    hi = n - 1;
    Stack *s = stack_create(n);
    assert(stack_push(s, lo));
    assert(stack_push(s, hi));
    while (!stack_empty(s)) {
        assert(stack_pop(s, &hi));
        assert(stack_pop(s, &lo));
        p = partition(arr, lo, hi);
        if (lo < p) {
            assert(stack_push(s, lo));
            assert(stack_push(s, p));
        }
        if (hi > p + 1) {
            assert(stack_push(s, p + 1));
            assert(stack_push(s, hi));
        }
    }
}

// Quicksort with queue
void quick_sort_queue(uint32_t *arr, uint32_t n) {
    moves = 0;
    compares = 0;
    max_queue_size = 0;
    int64_t p, lo, hi;
    lo = 0;
    hi = n - 1;
    Queue *q = queue_create(n);
    assert(enqueue(q, lo));
    assert(enqueue(q, hi));
    while (!queue_empty(q)) {
        assert(dequeue(q, &lo));
        assert(dequeue(q, &hi));
        p = partition(arr, lo, hi);
        if (lo < p) {
            assert(enqueue(q, lo));
            assert(enqueue(q, p));
        }
        if (hi > p + 1) {
            assert(enqueue(q, p + 1));
            assert(enqueue(q, hi));
        }
    }
}
// int main(void) {
//     uint32_t test[5] = { 5, 4, 3, 2, 1 };
//     quick_sort_queue(test, 5);
//     for (int i = 0; i < 5; i++) {
//         printf("%d, ", test[i]);
//     }
//     printf("\n");
// }
