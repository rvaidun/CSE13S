#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// Implemented using min heap
struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
};

static inline int parent_index(uint32_t i) {
    return (int) (i - 1) / 2;
}

static inline uint32_t left_index(uint32_t i) {
    return 2 * i + 1;
}

static inline uint32_t right_index(uint32_t i) {
    return 2 * i + 2;
}

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->capacity = capacity;
        pq->size = 0;
        pq->items = malloc(capacity * sizeof(Node));
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

// Swaps two elements in the priority queue
void pq_swap(PriorityQueue *q, uint32_t i, uint32_t j) {
    Node *temp = q->items[i];
    q->items[i] = q->items[j];
    q->items[j] = temp;
}

void pq_heap_up(PriorityQueue *q) {
    uint32_t i = q->size - 1;

    // If the parent is a parent and
    // the parent frequency is greater than the current frequency
    // Swap and set new
    while (parent_index(i) >= 0 && q->items[parent_index(i)]->frequency > q->items[i]->frequency) {

        pq_swap(q, parent_index(i), i);
        i = parent_index(i);
    }
}

void pq_heap_down(PriorityQueue *q) {
    int i = 0;
    // printf("pq_heap_down\n");
    // If the left index is not the last index
    while (left_index(i) < q->size) {
        // Guess that the smallest child is the left index
        int smallest_child_index = left_index(i);

        // If there is a right child check if right child is less than the left index
        if (right_index(i) < q->size
            && q->items[right_index(i)]->frequency < q->items[left_index(i)]->frequency) {
            smallest_child_index = right_index(i);
        }

        // If the frequency of current index is more than frequency of smallest index
        // Swap the two and move i down
        // Else we have succesfully heapified the array
        if (q->items[i]->frequency > q->items[smallest_child_index]->frequency) {
            pq_swap(q, i, smallest_child_index);
        } else {
            break;
        }
        i = smallest_child_index;
    }
    // printf("pq_heap_down FINISH\n");
}
// returns true if the priority queue is empty
bool pq_empty(PriorityQueue *q) {
    return q->size == 0;
}

// returns true if the priority queue is full
bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Adds a new node to the heap
bool enqueue(PriorityQueue *q, Node *n) {
    if (q->size == q->capacity) {
        return false; // Queue is full
    }
    q->items[q->size] = n;
    q->size++;
    pq_heap_up(q);
    return true;
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
    printf("dequeued successfully\n");
    pq_heap_down(q);
    printf("WHAT\n");
    return true;
}

// Prints a priority Queue
// Not implemented yet
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i++) {
        node_print(q->items[i]);
    }
}
