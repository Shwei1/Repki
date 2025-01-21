#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Passenger{
    int i;
    int b_count;
    double b_mass;
} Passenger;

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

    Passenger p;

    while (fscanf(txt_file, "%d %d %lf", &p.i, &p.b_count, &p.b_mass) == 3) {
        fwrite(&p, sizeof(Passenger), 1, bin_file);
    }

    fclose(txt_file);
    fclose(bin_file);
    printf("Successfully converted '%s' to binary '%s'.\n", txt_filename, bin_filename);
}


void convert_names_to_bin(const char *txt_filename, const char *bin_filename) {
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

    char name[25];
    while (fscanf(txt_file, "%24s", name) == 1) {
        fwrite(name, sizeof(char), 25, bin_file);
    }

    fclose(txt_file);
    fclose(bin_file);
    printf("Successfully converted '%s' to binary '%s'.\n", txt_filename, bin_filename);
}



void read_collection(FILE *f, Passenger **arr, int *c, int *s) {
    Passenger temp;

    while (fread(&temp, sizeof(Passenger), 1, f) == 1) {
        if (*s == *c) {
            *c *= 2;
            Passenger *temp_arr = realloc(*arr, *c * sizeof(Passenger));
            if (temp_arr == NULL) {
                perror("Failed to reallocate memory");
                exit(1);
            }
            *arr = temp_arr;
        }
        (*arr)[*s] = temp;
        (*s)++;
    }
}




void readnames(FILE *f, char ***narr, int *c, int *s) {
    char name[25];

    while (fread(name, sizeof(char), 25, f) == 25) {
        if (*s == *c) {
            *c *= 2;
            *narr = realloc(*narr, *c * sizeof(char *));
            if (*narr == NULL) {
                perror("Failed to reallocate memory");
                exit(1);
            }
        }

        (*narr)[*s] = malloc(strlen(name) + 1);
        if ((*narr)[*s] == NULL) {
            perror("Failed to allocate memory for name");
            exit(1);
        }
        strcpy((*narr)[*s], name);
        (*s)++;
    }
}






void output(Passenger *arr, char **narr, int size){
    for (int i = 0; i < size; i++){
        printf("Passenger %s No. %d with %d pieces of luggage with overall mass %.2lf.\n", narr[i] ,arr[i].i, arr[i].b_count, arr[i].b_mass);
    }
}



double mean_mass(Passenger *arr, int size){
    double total_mass = 0;
    int total_count = 0;
    for (int i = 0; i < size; i++){
        total_mass += arr[i].b_mass;
        total_count += arr[i].b_count;
    }
    return total_mass / total_count;
}



void find_passenger(Passenger *arr, char **narr, int size, double a){
    int count = 0;
    for (int j = 0; j < size; j++) {
        if (arr[j].b_mass/arr[j].b_count + a <= mean_mass(arr, size)){
            printf("Passenger No. %d %s", arr[j].i, narr[j]);
            count = 1;
            break;
        }
    }

    if (!count)
        printf("None have been found.");

}

void free_all(Passenger *arr, char **narr, int size){
    free(arr);
    for (int k = 0; k < size; k++){
        free(narr[k]);
    }
    free(narr);
}





int main() {
    const char *txt_filename1 = "input1111a1.txt";
    const char *txt_filename2 = "input1111a2.txt";
    const char *bin_filename1 = "input1111a1.bin";
    const char *bin_filename2 = "input1111a2.bin";

    int capacity1 = 2, size1 = 0;
    int capacity2 = 2, size2 = 0;
    Passenger *p = malloc(capacity2 * sizeof(Passenger));
    char **names = malloc(capacity1 * sizeof(char *));

    if (p == NULL || names == NULL) {
        perror("Allocation failed");
        return 1;
    }


    convert_txt_to_bin(txt_filename2, bin_filename2);
    convert_names_to_bin(txt_filename1, bin_filename1);


    FILE *f1 = fopen(bin_filename1, "rb");
    FILE *f2 = fopen(bin_filename2, "rb");

    if (f1 == NULL || f2 == NULL) {
        perror("Failed to open files for reading");
        free(p);
        free(names);
        return 1;
    }


    read_collection(f2, &p, &capacity2, &size2);
    readnames(f1, &names, &capacity1, &size1);


//    output(p, names, size2);

    double a;
    printf("Enter the value of deviation: ");
    scanf("%lf", &a);

    find_passenger(p, names, size1, a);


    free_all(p, names, size1);
    fclose(f1);
    fclose(f2);

    return 0;
}