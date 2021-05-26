#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->prev = NULL;
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->tail->next = NULL;
        ll->mtf = mtf;
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
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        count++;
    }
    return count;
}

// Code taken from the Lecture on Linked Lists and modified slightly
// to work with structures in this assignment
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks++;
    for (Node *curr = ll->head; curr != NULL; curr = curr->next, links++) {
        if (curr->oldspeak == NULL) {
            continue;
        }
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            return curr;
        }
    }
    links -= 1;
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    Node *n = ll_lookup(ll, oldspeak);
    if (n != NULL) {
        return;
    }

    n = node_create(oldspeak, newspeak);
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next->prev = n;
    ll->head->next = n;
}

void ll_insert_from_node(LinkedList *ll, Node *n) {
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next->prev = n;
    ll->head->next = n;
    return;
}

void ll_print(LinkedList *ll) {
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        node_print(curr);
    }
    return;
}
