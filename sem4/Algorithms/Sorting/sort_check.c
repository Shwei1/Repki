#include "sort_check.h"

bool sorted(long *arr, size_t size){
    
    if (size < 2) return true;

    for (size_t i = 0; i < size - 1; ++i) {
        if (arr[i+1] < arr[i])  
            return false;
    }
    return true;
}
