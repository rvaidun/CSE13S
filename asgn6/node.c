#include "node.h"

#include <stdio.h>
#include <stdlib.h> // For null
#include <inttypes.h>
// Creates a new node and sets symbol and frequency. Return the node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

// Deletes a node
void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

// Joins the left and the right node and returns a new node
Node *node_join(Node *left, Node *right) {
    Node *n = (Node *) malloc(sizeof(Node));
    printf("CREATED NODE IN JOIN\n");
    if (n) {
        n->frequency = left->frequency + right->frequency;
        n->symbol = '$';
        printf("FINISHED SYMBOL IN JOIN\n");
        n->right = right;
        n->left = left;
        printf("SET RIGHT AND LEFT SYMBOL IN JOIN\n");
    }
    printf("CAME OUT OF FOR LOOP, RETURNING n\n");
    return n;
}

// Debugger function to print a node
// NOT IMPLEMENTED YET
void node_print(Node *n) {
    printf("%c %" PRIu64 "\n", n->symbol, n->frequency);
}
