#include "bubble.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
extern uint32_t moves, compares;

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
}

// int main(void) {
//     uint32_t test[5] = { 5, 4, 3, 2, 1 };
//     bubble_sort(test, 5);
//     for (int i = 0; i < 5; i++) {
//         printf("%d, ", test[i]);
//     }
// }
