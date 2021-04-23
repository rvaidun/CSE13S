// Rahul Vaidun
// April 2021

#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // For srandom and random
#include <unistd.h> // For getopt().
#define OPTIONS "absqQr:n:p:"
uint32_t moves, compares;
uint32_t max_stack_size, max_queue_size;

int main(int argc, char **argv) {
    int opt = 0, print_elements = 100, seed = 13371453;
    uint32_t size = 100;
    uint32_t random_arr[size], sorted_arr[size];
    char *first_invalid;

    enum sorts { BUBBLE, SHELL, QUICK_STACK, QUICK_QUEUE, UNKNOWN };
    void (*func_ptr[4])(uint32_t * arr, u_int32_t n)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };
    char *sorts_strings[]
        = { "Bubble Sort", "Shell Sort", "Quick Sort (Stack)", "Quick Sort (Queue)" };
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
            seed = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                printf("Invalid argument for %c - %s", opt, optarg);
            }
            break;
        case 'n':
            // Set optarg to size
            size = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                printf("Invalid argument for %c - %s", opt, optarg);
            }
            break;
        case 'p':
            // Set optarg to print_elements
            print_elements = strtoul(optarg, &first_invalid, 10);
            if (*first_invalid != '\0') {
                printf("Invalid argument for %c - %s", opt, optarg);
            }
            break;
	default: s = set_insert(s, UNKNOWN); break;
        }
    }
    if (set_member(s, UNKNOWN)) {
        printf("SYNOPSIS\n"
               "   A collection of comparison-based sorting algorithms.\n"
               "USAGE\n"
               "./sorting [-habsqQo] [-n length] [-p elements] [-r seed]\n\n"
               "OPTIONS\n"
               "   -h              Display program help and usage.\n"
               "   -a              Enable all sorts.\n"
               "   -b              Enable Bubble Sort.\n"
               "   -s              Enable Shell Sort.\n"
               "   -q              Enable Quick Sort (Stack).\n"
               "   -Q              Enable Quick Sort (Queue).\n"
               "   -n length       Specify number of array elements.\n"
               "   -p elements     Specify number of elements to print.\n"
               "   -r seed         Specify random seed.\n"
               "   -o              Use sorted arrays.\n");
	return -1;
    }
    srandom(seed); // Set the seed
    // Creates random array
    for (uint32_t i = 0; i < size; i++) {
        random_arr[i] = random();
    }

    for (int i = 0; i < UNKNOWN; i++) {
        if (set_member(s, i)) {

            for (uint32_t i = 0; i < size; i++) {
                sorted_arr[i] = random_arr[i];
            }
            func_ptr[i](sorted_arr, size);
            printf("%s\n", sorts_strings[i]);
            printf("%d elements, %d moves, %d compares\n", size, moves, compares);
	    if (i == QUICK_STACK) {
		printf("Max stack size: %d\n",max_stack_size);
	    } else if (i == QUICK_QUEUE) {
		printf("Max queue size: %d\n",max_queue_size);
	    }
            for (uint32_t i = 0; i < size; i++) {
                if (i % 5 == 0 && i != 0) {
                    printf("\n");
                }
                printf("%13" PRIu32, sorted_arr[i]);

                if (i == size - 1) {
                    printf("\n");
                }
            }
        }
    }
}
