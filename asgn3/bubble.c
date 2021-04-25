#include "sorting.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// // Implementation of Bubble Sort
// // Uses the Pseudocode for bubble_sort provided in the assignment PDF
void bubble_sort(uint32_t *arr, uint32_t n) {
    bool swapped = true;
    uint32_t temp;
    moves = 0;
    compares = 0;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i++) {
            compares++;
            if (arr[i] < arr[i - 1]) {
                moves += 3;
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = true;
            }
        }
        n -= 1;
    }
    return;
}
