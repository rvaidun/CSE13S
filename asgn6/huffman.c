#include "huffman.h"

#include "code.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdio.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *n;
    Node *left;
    Node *right;
    Node *joined;

    PriorityQueue *pq = pq_create(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            n = node_create(i, hist[i]);
            enqueue(pq, n);
        }
    }
    while (pq_size(pq) > 1) {
        dequeue(pq, &left);
        dequeue(pq, &right);
        node_join(left, right);
        enqueue(pq, joined);
    }

    dequeue(pq, &joined);
    pq_delete(pq);
    return joined;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    uint8_t bit;
    if (root) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, &bit);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &bit);
        }
    }
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Node *n;
    Node *right;
    Node *left;
    Stack *s = stack_create(nbytes);
    for (int i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
            n = node_create(tree_dump[++i], i);
            stack_push(s, n);
        } else {
            stack_pop(s, &right);
            stack_pop(s, &left);
            stack_push(s, node_join(left, right));
        }
    }
    stack_pop(s, &n);
    stack_delete(&s);
    return n;
}

void delete_tree(Node **root) {
    delete_tree((*root)->left);
    delete_tree((*root)->right);
    node_delete(root);
}
