#include <stdio.h>
#define N 100

void print(int matrix[][N], int n) {
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void input(int matrix[][N], int n) {
    int size = 2 * n;
    for (int i = 0; i < size; i++) {
        printf("Input %i numbers for row %i:\n", size, i + 1);
        for (int j = 0; j < size; j++) {
            scanf("%i", &matrix[i][j]);
        }
    }
}
//
//void turn_270(int matrix[][N], int n) {
//    int size = 2 * n;
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            printf("%i ", matrix[j][3-i]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}

void turn_270(int matrix[][N], int matrix_270[][N], int n) {
    int size = 2 * n;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_270[i][j] = matrix[j][size-1-i];
        }

    }

}

int main() {
    int n;
    printf("Enter the order of the matrix: ");
    scanf("%i", &n);
    int matrix[N][N];
    int matrix_270[N][N];

    input(matrix, n);
    printf("\n\033[34mOriginal matrix:\033[0m\n");
    print(matrix, n);
    printf("\n\033[32mRotated matrix:\033[0m\n");
    turn_270(matrix, matrix_270, n);
    print(matrix_270, n);

}