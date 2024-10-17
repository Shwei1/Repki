#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Passenger{
    int i;
    int b_count;
    double b_mass;
} Passenger;

void read_collection(FILE *f, Passenger **arr, int *c, int *s, char *buffer, size_t buffer_size){
    int index;
    int baggage_count;
    double baggage_mass;

    while (fgets(buffer, buffer_size, f) != NULL) {
        sscanf(buffer, "%d %d %lf", &index, &baggage_count, &baggage_mass);
        if (*s == *c) {
            *c *= 2;
            Passenger *temp = realloc(*arr, *c * sizeof(Passenger));

            *arr = temp;
        }

        (*arr)[(*s)].i = index;
        (*arr)[(*s)].b_count = baggage_count;
        (*arr)[(*s)].b_mass = baggage_mass;

        (*s)++;
    }
}


void readnames(FILE *f, char ***narr, int *c, int *s){
    char name[25];

    while (fscanf(f, "%24s", name) == 1) {
        if (*s == *c) {
            *c *= 2;
            *narr = realloc(*narr, *c * sizeof(char*));
        }

        (*narr)[*s] = malloc(strlen(name) + 1);
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





int main(){
    FILE *f1;
    const char *filename1 = "input1111a1.txt";
    FILE *f2;
    const char *filename2 = "input1111a2.txt";
    int capacity1 = 2;
    int size1 = 0;
    int capacity2 = 2;
    int size2 = 0;
    char buffer[256];
    Passenger *p = NULL;
    char **names = NULL;
    double a;

    p = (Passenger *)malloc(capacity1 * sizeof(Passenger));
    names = (char **) malloc(capacity2 * sizeof(char*));

    f1 = fopen(filename1, "r");
    f2 = fopen(filename2, "r");

    read_collection(f2, &p, &capacity2, &size2, buffer, 256);
    readnames(f1, &names, &capacity1, &size1);


//    output(p, names, size2);
    printf("Enter the value of deviation: ");
    scanf("%lf", &a);

    find_passenger(p, names, size1, a);
    free_all(p, names, size1);
    fclose(f1);
    fclose(f2);



}