#include "gaps.h"

#include <stdio.h>

// Implementation of Shell sort
// Uses the Pseudocode for shell sort provided in the assignment PDF
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
