#include "selection_sort.h"

void selection_sort(long *arr, size_t size){
    for (size_t i = 0; i < size-1; ++i) {
        size_t min_index = i;
        for (size_t j = i+1; j < size; ++j) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (min_index != i) {
            long buffer = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = buffer;
        }
    }
}
