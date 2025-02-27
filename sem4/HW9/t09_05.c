#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long general;
    long special;
} robot;

void merge(robot* arr, size_t left, size_t mid, size_t right){
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    robot* L = (robot *) malloc(n1 * sizeof(robot));
    robot* R = (robot *) malloc(n2 * sizeof(robot));

    for (size_t i = 0; i < n1; ++i){
        L[i] = arr[left+i];
    }
    for (size_t j = 0; j < n2; ++j){
        R[j] = arr[mid+1+j];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < n1 && j < n2){
        if (L[i].general > R[j].general)
            arr[k++] = R[j++];
        else
            arr[k++] = L[i++];
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L); free(R);
}

void merge_sort(robot* arr, size_t left, size_t right){
    if (left == right)
        return;
    size_t mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

int main() {
   int N;

   scanf("%d", &N);

   robot *robots = (robot *) malloc(N * sizeof(robot));
   for (size_t i = 0; i < N; ++i){
        long general, special;
        scanf("%ld %ld", &general, &special);
        robots[i] = (robot){general, special};
   }

   merge_sort(robots, 0, N-1);

   for (size_t j = 0; j < N; ++j){
        printf("%ld %ld\n", robots[j].general, robots[j].special);
   }

   free(robots);
}

