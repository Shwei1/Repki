#include <stdio.h>
#include <stdlib.h>

void convert_txt_to_bin(const char *txt_filename, const char *bin_filename) {
    FILE *txt_file = fopen(txt_filename, "r");
    if (txt_file == NULL) {
        perror("Failed to open text file");
        exit(1);
    }

    FILE *bin_file = fopen(bin_filename, "wb");
    if (bin_file == NULL) {
        perror("Failed to open binary file");
        fclose(txt_file);
        exit(1);
    }

    double num;

    while (fscanf(txt_file, "%lf", &num) == 1) {
        fwrite(&num, sizeof(double), 1, bin_file);
    }

    fclose(txt_file);
    fclose(bin_file);
    printf("Successfully converted '%s' to binary '%s'.\n", txt_filename, bin_filename);
}

void append_nums(FILE *f, double **arr, int *c, int *s){
    double n;
    while (fread(&n, sizeof(double),1, f) == 1) {
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
    char bin_filename[] = "input1107ye.bin";

    numbers = (double *)malloc(capacity * sizeof(double));


    convert_txt_to_bin(filename, bin_filename);

    f = fopen(bin_filename, "rb");

    if (f == NULL) {
        perror("Failed to open files for reading");
        free(numbers);
        return 1;
    }

    append_nums(f, &numbers, &capacity, &size);

    double M = findmax(numbers, size);
    double m = findmin(numbers, size);

    printf("The sum of the smallest and largest number in your file is %lf", M+m);

    free(numbers);
    fclose(f);
}
