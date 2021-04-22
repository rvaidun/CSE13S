// Rahul Vaidun
// April 2021

#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // For srandom and random
#include <string.h> // For memcpy
#include <unistd.h> // For getopt().

#define OPTIONS "absqQr:n:p:"

int main(int argc, char **argv) {
    int opt = 0, size = 100, print_elements = 100, seed = 13371453;
    uint32_t random_arr[size], sorted_arr[size];
    typedef enum sorts { BUBBLE, SHELL, QUICK_STACK, QUICK_QUEUE, DONE } sorts;
    void (*func_ptr[4])(uint32_t arr, u_int32_t n)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };
    Set s = set_empty();

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            s = set_insert(s, BUBBLE);
            s = set_insert(s, SHELL);
            s = set_insert(s, QUICK_STACK);
            s = set_insert(s, QUICK_QUEUE);
            break;
        case 'b': s = set_insert(s, BUBBLE); break;
        case 's': s = set_insert(s, SHELL); break;
        case 'q': s = set_insert(s, QUICK_STACK); break;
        case 'Q': s = set_insert(s, QUICK_QUEUE); break;
        case 'r':
            // Set optarg to seed
            srandom(strtoul(optarg, &seed, 10));
            break;
        case 'n':
            // Set optarg to size
            strtoul(optarg, &size, 10);
            break;
        case 'p':
            // Set optarg to print_elements
            strtoul(optarg, &print_elements, 10);
            break;
        default: break;
        }
    }
    // Creates random array
    for (int i = 0; i < size; i++) {
        random_arr[i] = random();
    }

    for (int i = 0; i < DONE; i++) {
        if (set_member(s, i)) {

            for (int i = 0; i < size; i++) {
                sorted_arr[i] = random_arr[i];
            }
            func_ptr[i](sorted_arr, size);
        }
    }
}
