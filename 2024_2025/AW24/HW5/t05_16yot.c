#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long double series(int k, long double x, long double epsilon) {
    long double sum = 0;
    long double term;
    term = pow(-1, k + 1) * powl(x, 2 * k - 2);
    if (fabsl(term) > epsilon)
        return sum + term + series(k+1, x, epsilon);
    else {
        return 1 + sum;
    }



}


int main() {
    long double epsilon;
    long double x;

    do {
        printf("Enter the value of x and the value of error: ");
        scanf("%Lf %Lf", &x, &epsilon);
        if (fabsl(x) > 1) {
            printf("%sDOMAIN ERROR.%s |x| must be strictly less than 1.\n", "\033[31m", "\033[0m");
        }
    } while (fabsl(x) > 1);

    printf("%Lf", series(1, x, epsilon));

}
