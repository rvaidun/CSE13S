#include "gaps.h"

#include <stdio.h>

void shell_sort(uint32_t *arr, uint32_t n) {
    extern uint32_t moves, compares;
    moves = 0;
    compares = 0;
    for (uint32_t gap = 0; gap < GAPS; gap++) {
        for (uint32_t i = gaps[gap]; i < n; i++) {
            uint32_t j = i;
            moves++;
            uint32_t temp = arr[i];
            while (j >= gaps[gap] && ++compares && temp < arr[j - gaps[gap]]) {
                moves++;
                arr[j] = arr[j - gaps[gap]];
                j -= gaps[gap];
            }
            moves++;
            arr[j] = temp;
        }
    }
}

// int main(void) {
//     uint32_t test[5] = { 5, 4, 3, 2, 1 };
//     shell_sort(test, 5);
//     for (int i = 0; i < 5; i++) {
//         printf("%d, ", test[i]);
//     }
// }
