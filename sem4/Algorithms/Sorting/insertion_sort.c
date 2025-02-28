#include "insertion_sort.h"

void insertion_sort(long *arr, size_t size){
    for (size_t i = 0; i < size; ++i) {
        long key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j-1] > key) {
            arr[j] = arr[j-1];
            j--;
        }
        
        arr[j] = key;
    }
}
