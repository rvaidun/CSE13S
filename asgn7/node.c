#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct Node {
//     char *oldspeak;
//     char *newspeak;
//     Node *next;
//     Node *prev;
// };

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->next = NULL;
        n->prev = NULL;
        if (oldspeak) {
            n->oldspeak = malloc(strlen(oldspeak) + 1);
            if (n->oldspeak) {
                strcpy(n->oldspeak, oldspeak);

            } else {
                free(n->oldspeak);
                n->oldspeak = NULL;
            }
        } else {
            n->oldspeak = NULL;
        }
        if (newspeak) {
            n->newspeak = malloc(strlen(newspeak) + 1);
            if (n->newspeak) {
                strcpy(n->newspeak, newspeak);
            } else {
                free(n->newspeak);
                n->newspeak = NULL;
            }
        } else {
            n->newspeak = NULL;
        }
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
    if (n->oldspeak && n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else {
        printf("%s\n", n->oldspeak);
    }
    return;
}
