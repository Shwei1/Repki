#include "bubble_sort.h"

void bubble_sort(long *arr, size_t size){
    for (size_t i = 0; i < size; ++i){
        bool swapped = false;
        for (size_t j = 1; j < size; ++j) {
            if (arr[j-1] > arr[j]){
                long buffer = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = buffer;
                swapped = true;
            }
        }
        if (!swapped)
            return;
    }
}

