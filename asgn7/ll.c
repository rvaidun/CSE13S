#include "ll.h"

#include "node.h"

#include <stdlib.h>
struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->head = (Node *) malloc(sizeof(Node));
        ll->tail = (Node *) malloc(sizeof(Node));
        ll->head->prev = NULL;
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->tail->next = ll->head;
    }
    return ll;
}

// Destructor for a linked list
// Code taken from the Lecture slides on Linked Lists and slightly modified
void ll_delete(LinkedList **ll) {
    if (*ll) {
        while ((*ll)->head != NULL) {
            Node *next = NULL;
            next = (*ll)->head->next;
            node_delete(&(*ll)->head);
            (*ll)->head = next;
        }
    }
    free(*ll);
    return;
}

uint32_t ll_length(LinkedList *ll) {
    uint32_t count = 0;
    for (Node *curr = ll->head; curr != NULL; curr = curr->next) {
        count++;
    }
    return count;
}

// Code taken from the Lecture on Linked Lists and modified slightly
// to work with structures in this assignment
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *curr = ll->head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            return curr;
        }
        return NULL;
    }
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    Node *n = ll_lookup(ll, oldspeak);
    if (n != NULL) {
        return n;
    }
    n = node_create(oldspeak, newspeak);
    n->next = ll->head;
    ll->head = n;
}

void ll_insert_from_node(LinkedList *ll, Node *n) {
    Node *nl = NULL;
    nl->next = ll->head;
    ll->head = n;
}

void ll_print(LinkedList *ll) {
    for (Node *curr = ll->head->next; curr != NULL; curr = curr->next) {
        node_print(curr);
    }
}
