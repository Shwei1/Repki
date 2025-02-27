#include <stdio.h>
#include <stdlib.h>

void quick_sort(int* arr, size_t a, size_t b) {
    if (a >= b) return;

    int pivot = arr[a+(b-a)/2];
    size_t left = a;
    size_t right = b;

    while(1){

        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        
        if (left > right) break;

        int buffer = arr[left];
        arr[left] = arr[right];
        arr[right] = buffer;
        left++; if (right != 0) right--;
    
    }

    if (right > a)
        quick_sort(arr, a, right);
    quick_sort(arr, left, b);
}

int main() {
   int N;
   scanf("%d", &N);

   int* arr = (int*) malloc(N * sizeof(int));

   for (size_t i = 0; i < N; ++i){
        scanf("%d", &arr[i]);
   }

   quick_sort(arr, 0, N-1);

   for (size_t j = 0; j < N; ++j){
        printf("%d ", arr[j]);
   }

   free(arr);
   return 0;
}

