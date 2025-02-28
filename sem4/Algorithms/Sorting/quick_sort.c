#include "quick_sort.h"

void quick_sort(long* arr, size_t low, size_t high){
    if (low >= high) return;

    long pivot = arr[low + (high - low) / 2];

    size_t left = low;
    size_t right = high;

    while(1) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left > right) break;

        long buffer = arr[left];
        arr[left] = arr[right];
        arr[right] = buffer;
        left++;
        if (right > 0) right--;
    }

    if (right > low)
        quick_sort(arr, low, right);
    quick_sort(arr, left, high);
}
