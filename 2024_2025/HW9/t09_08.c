#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean(const double *set, int size){
    double sum = 0;
    for (int j = 0; j < size; j++)
        sum += set[j];
    return sum / size;
}


void dispersion(double *arr, double *darr, double mean, int n){
    for (int k = 0; k < n; k++){
        darr[k] = fabs(mean - arr[k]);
    }
}

int main(){
    int n;

    printf("Enter the size of your array: ");
    scanf("%d", &n);

    double *arr = (double *) calloc(n, sizeof(double));
    double *dispersion_array = (double *) calloc(n, sizeof(double));

    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++){
        scanf("%lf", &arr[i]);
    }

    printf("Your mean value is %lf\n", mean(arr, n));

    dispersion(arr, dispersion_array, mean(arr, n), n);

    printf("Your dispersion is: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", *(dispersion_array + i));
    }

    free(dispersion_array);
    free(arr);
}