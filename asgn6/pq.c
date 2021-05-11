#include "pq.h"

#include <stdbool.h>
#include <stdlib.h>

// Implemented using min heap
struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->capacity = capacity;
        pq->size = 0;
    }
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (*q) {
        free(*q);
        *q = NULL;
    }
    return;
}

inline uint32_t parent_index(uint32_t i) {
    return (i - 1) / 2;
}

// Swaps two elements in the priority queue
void pq_swap(PriorityQueue *q, uint32_t i, uint32_t j) {
    uint32_t temp = q->items[i];
    q->items[i] = q->items[j];
    q->items[j] = temp;
}

// Removes the element with the smallest Frequency
bool dequeue(PriorityQueue *q, Node **n) {
    // If the size is 0 there is nothing to dequeue.
    if (q->size == 0) {
        return false;
    }
    *n = q->items[0];
    q->items[0] = q->items[q->size - 1];
    q->size--;
    pq_heap_down();
    return true;
}

// Adds a new node to the heap
bool enqueue(PriorityQueue *q, Node *n) {
    if (q->size == q->capacity) {
        return false; // Queue is full
    }
    q->items[q->size] = n;
    q->size++;
    pq_heap_up(q);
    return false;
}

void pq_heap_up(PriorityQueue *q) {
    uint32_t index = q->size - 1;
    // bool has_parent = parent_index(index) >= 0;
    // bool parent_larger = q->items[parent_index(index)] > q->items[index];

    while (parent_index(index) >= 0 && q->items[parent_index(index)] > q->items[index]) {
        swap(parent_index(index), index);
        index = parent_index(index);
    }
}
