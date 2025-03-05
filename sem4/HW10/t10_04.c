#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate_permutations_(int *arr, int count, int n, int k){
    if (count == k){
        for (int i = 0; i < k; i++)
            printf("%d ", arr[i]);
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; ++i){
        bool is_in = false;
        for (int j = 0; j < count; ++j){
            if (arr[j] == i) {
                is_in = true;
                break;
            }
        }

        if (!is_in){
            arr[count] = i;
            generate_permutations_(arr, count+1, n, k);
        }
    }
}


void generate_permutations(int n, int k){
    int *arr = (int*) calloc(k, sizeof(int));
    generate_permutations_(arr, 0, n, k);
    free(arr);
}


int main(void){
    int n, k;
    scanf("%d %d", &n, &k);
    generate_permutations(n, k);
    return 0;
}
