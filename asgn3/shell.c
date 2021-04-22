#include "gaps.h"

#include <stdio.h>

void shell_sort(uint32_t *arr, uint32_t n) {
    for (uint32_t gap = 0; gap < GAPS; gap++) {
        for (uint32_t i = gaps[gap]; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = arr[i];
            while (j >= gaps[gap] && temp < *(arr + j - gaps[gap])) {
                *(arr + j) = arr[j - gaps[gap]];
                j -= gaps[gap];
            }
            *(arr + j) = temp;
        }
    }
}

int main(void) {
    uint32_t test[5] = { 5, 4, 3, 2, 1 };
    shell_sort(test, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d, ", test[i]);
    }
}
