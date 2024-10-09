#include <stdio.h>
#include <stdlib.h>

void upgrade_matrix(double **matrix, double ***umatrix, int row1, int col1){
    int newcol = col1 + (int)(col1/2);
    *umatrix = (double**) malloc(row1 *sizeof(double*));
    for (int i = 0; i < row1; i++){
        (*umatrix)[i] = (double *)calloc(newcol, sizeof(double));
    }
    for (int i = 0; i < row1; i++) {
        int k = 0;
        for (int j = 0; j < col1; j++){
            if (j % 2 == 0) {
                (*umatrix)[i][k] = matrix[i][j];
                k++;
            }
            else {
                (*umatrix)[i][k] = matrix[i][j];
                k+=2;
                continue;
            }
        }
    }

}

void allocate(double **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        matrix[i] = (double *) malloc(col * sizeof(double));
    }
}

void free_matrix(double **matrix, int rows){
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

void input(double **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        printf("Enter %d numbers for row %d: ", col, i+1);
        for (int j = 0; j < col; j++){
            scanf("%lf", (*(matrix + i) + j));
        }
    }
}

void output(double **matrix, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%lf ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int M;
    int N;

    printf("Enter your matrix dimensions: ");
    scanf("%d %d", &N, &M);

    double **matrix = (double **)malloc(N * sizeof(double*));
    double **upgraded_matrix;

    allocate(matrix, N, M);

    input(matrix, N, M);
    output (matrix, N, M);

    upgrade_matrix(matrix, &upgraded_matrix, N, M);

    M += (int)(M / 2);

    output(upgraded_matrix, N, M);




    free_matrix(matrix, N);
    free_matrix(upgraded_matrix, N);
}