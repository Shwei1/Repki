#include <stdio.h>
#include <math.h>
#define N 100

int is_cube(int n) {
    int cube_root = round(cbrt(n));
    return (cube_root * cube_root * cube_root == n);
}

int cube_counter(int arr[N], int num) {
    int counter = 0;
    for (int i = 0; i < num; i++) {

        if (is_cube(arr[i]) && arr[i] % 2 == 0) {
            counter++;
        }
    }
    return counter;
}



int main() {
    int arr[N];
    int num;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &num);


    printf("Enter %d numbers:\n", num);
    for (int i = 0; i < num; i++) {
        scanf("%i", &arr[i]);
    }

    printf("%d", cube_counter(arr, num));





}

