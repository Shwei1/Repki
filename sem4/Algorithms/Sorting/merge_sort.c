#include "merge_sort.h"

void merge(long* arr, long* aux, size_t left, size_t mid, size_t right){
    for (size_t i = left; i <= right; ++i)
        aux[i] = arr[i];


    size_t i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (aux[i] <= aux[j])
            arr[k++] = aux[i++];
        else
            arr[k++] = aux[j++];
    }

    while (i <= mid)
        arr[k++] = aux[i++];
}



void merge_sort_(long *arr, long* aux, size_t left, size_t right){
    if (left == right)
        return;
    size_t mid = left + (right - left) / 2;
    merge_sort_(arr, aux, left, mid);
    merge_sort_(arr, aux, mid+1, right);
    merge(arr, aux, left, mid, right);
}


void merge_sort(long *arr, size_t size){
    long *aux = (long *) malloc(size * sizeof(long));
    if (aux == NULL){
        perror("Memory allocation failed at merge_sort().\n");
        return;
    }
    
    merge_sort_(arr, aux, 0, size-1);
    free(aux);
}












