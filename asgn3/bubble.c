#include <stdbool.h>
#include <stdint.h>

void bubble_sort(uint32_t *arr, uint32_t n) {
    bool swapped = true;
    uint32_t temp;

    while (swapped) {
	swapped = false;
	for (int i = 1; i < n; i++) {
	    if (*(arr + i) < *(arr + i - 1)) {
		temp = *(arr + i);
		*(arr + i) = *(arr + i - 1);
		*(arr +	i - 1) = temp;
		swapped = true;
	    }
	}
	n -= 1;
    }
}

