#include <stdio.h>
#define N 50

int min_even(int arr[N], int n) {
    int min_el = arr[1];
    for (int j = 1; j < n; j += 2) {
        if (min_el > arr[j])
            min_el = arr[j];
    }
    return min_el;

}

int max_odd(int arr[N], int n) {
    int max_el = arr[0];
    for (int j = 0; j < n; j += 2) {
        if (max_el < arr[j])
            max_el = arr[j];
    }
    return max_el;

}




int main() {
    int arr[N];
    int n;
    printf("Enter the number of numbers in array: ");
    scanf("%i", &n);
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    printf("%i", min_even(arr, n) + max_odd(arr, n));

}
