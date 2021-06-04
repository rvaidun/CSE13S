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
    *ll = NULL;
    return;
}

// Returns the number of nodes in the linked list
uint32_t ll_length(LinkedList *ll) {
    uint32_t count = 0;
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        count++;
    }
    return count;
}

// Code taken from the Lecture on Linked Lists and modified slightly
// to work with structures in this assignment
// Checks if a node exists in a linked list
// If node exists return the node
// Else return null
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks++;
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next, links++) {
        if (curr->oldspeak == NULL) {
            continue;
        }
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            if (ll->mtf && curr->prev != ll->head) {
                // Move to front
                curr->prev->next = curr->next; // Node before points to node after
                curr->next->prev = curr->prev; // Node after should point to node before
                curr->next = ll->head->next; // Node after curr should be heads next
                curr->prev = ll->head; // currs previous should be head
                ll->head->next->prev = curr; // Node after head should point back to curr
                ll->head->next = curr; // Heads next should be n
            }

            return curr;
        }
    }
    return NULL;
}

// Inserts a new node into the linked list if it isnt there

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // Check if node exists
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }

    Node *n = node_create(oldspeak, newspeak);
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next->prev = n;
    ll->head->next = n;
}

void ll_print(LinkedList *ll) {
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
        node_print(curr);
    }
    return;
}
