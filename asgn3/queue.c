#include "queue.h"

#include <stdlib.h>

struct Queue {
    u_int32_t head;
    u_int32_t tail;
    u_int32_t size;
    u_int32_t capacity;
    int64_t *items;
};

// Creates a queue
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

// Destructor for queue
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

// Returns true if queue is empty and false otherwise
bool queue_empty(Queue *q) {
    return q->head == q->tail;
}

// Returns true if the queue is full and false otherwise
bool queue_full(Queue *q) {
    return q->tail == q->capacity;
}

// Returns the number of items in the queue
uint32_t queue_size(Queue *q) {
    return q->size;
}

// Queues an item
bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q)) {
        return false;
    }
    q->items[q->tail] = x;
    q->tail++;
}

// Dequeues an item from the queue
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q)) {
        return false;
    }
    *x = q->items[q->head];
    q->head++;
}

// Prints the queue
void queue_print(Queue *q) {
    printf("{");
    for (uint32_t i = 0; i < q->capacity; i++) {
        printf("%lld", q->items[i]);
        printf(i != q->capacity - 1 ? ", " : "");
    }
    printf("}\n");
}
