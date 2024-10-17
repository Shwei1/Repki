#include <stdio.h>
#include <stdlib.h>

void append_nums(FILE *f, double **arr, int *c, int *s){
    double n;
    while (fscanf(f, "%lf", &n) == 1) {
        if (*s == *c) {
            *c *= 2;
            double *temp = realloc(*arr, *c * sizeof(double));
            if (temp == NULL) {
                printf("Memory allocation failed\n");
                free(*arr);
                exit(1);
            }
            *arr = temp;
        }
        (*arr)[(*s)++] = n;
    }
}


double findmax(double *arr, int s){
    double max_el = arr[0];
    for (int i = 0; i < s; i++){
        if (arr[i] > max_el){
            max_el = arr[i];
        }
    }
    return max_el;
}

double findmin(double *arr, int s){
    double min_el = arr[0];
    for (int i = 0; i < s; i++){
        if (arr[i] < min_el){
            min_el = arr[i];
        }
    }
    return min_el;
}



int main(){
    FILE *f;
    double *numbers = NULL;
//    double number;
    int capacity = 2;
    int size = 0;
    char filename[] = "input1107ye.txt";

    numbers = (double *)malloc(capacity * sizeof(double));

    f = fopen(filename, "r");

    append_nums(f, &numbers, &capacity, &size);

    double M = findmax(numbers, size);
    double m = findmin(numbers, size);

    printf("The sum of the smallest and largest number in your file is %lf", M+m);

    free(numbers);
    fclose(f);
}
