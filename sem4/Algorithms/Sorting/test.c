#include "array_generator.h"
#include "sort_check.h"
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

int main(void){
    long N;
    printf("Enter the size of array: ");
    scanf("%ld", &N);
    long *arr1 = generate_array(N);
    long *arr2 = (long *) malloc(N * sizeof(long));
    long *arr3 = (long *) malloc(N * sizeof(long));
    long *arr4 = (long *) malloc(N * sizeof(long));
    long *arr5 = (long *) malloc(N * sizeof(long));
    if (!arr2 || !arr3 || !arr4 || !arr5) {
        printf("Memory allocation failed at main().\n");
        goto end;
    }

    memcpy(arr2, arr1, N * sizeof(long));
    memcpy(arr3, arr1, N * sizeof(long));
    memcpy(arr4, arr1, N * sizeof(long));
    memcpy(arr5, arr1, N * sizeof(long));
    
    printf("Beginning to sort \033[91m%ld\033[0m elements...\n", N);

    clock_t start, end;
    double elapsed;

    start = clock();
    quick_sort(arr5, 0, N-1);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (sorted(arr5, N))
        printf("\033[92mSorted successfully by quick_sort(). Time elapsed: \033[94m%lf\033[0m.\n", elapsed);
    else
        printf("\033[31mSorting failed by quick_sort().\033[0m\n");

    start = clock();
    merge_sort(arr4, N);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (sorted(arr4, N))
        printf("\033[92mSorted successfully by merge_sort(). Time elapsed: \033[94m%lf\033[0m.\n", elapsed);
    else
        printf("\033[31mSorting failed by merge_sort().\033[0m\n");

    start = clock();
    insertion_sort(arr2, N);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (sorted(arr2, N))
        printf("\033[92mSorted successfully by insertion_sort(). Time elapsed: \033[94m%lf\033[0m.\n", elapsed);
    else
        printf("\033[31mSorting failed by insertion_sort().\033[0m\n");

    start = clock();
    selection_sort(arr3, N);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (sorted(arr3, N))
        printf("\033[92mSorted successfully by selection_sort(). Time elapsed: \033[94m%lf\033[0m.\n", elapsed);
    else
        printf("\033[31mSorting failed by selection_sort().\033[0m\n");

    start = clock();
    bubble_sort(arr1, N);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (sorted(arr1, N))
        printf("\033[92mSorted successfully by bubble_sort(). Time elapsed: \033[94m%lf\033[0m.\n", elapsed);
    else
        printf("\033[31mSorting failed by bubble_sort().\033[0m\n");

end:
    free(arr1); free(arr2); free(arr3); free(arr4); free(arr5);
    return 0;
}
