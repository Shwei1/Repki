#include <stdio.h>

long int factorial2k1(long int k) {
    long int product = 1;
    for (int i = 2; i <= 2*k+1; i++) {
        product *= i;
    }
    return product;
}

long double pow2k1(long double x, long int k){
    long double product = 1;
    for (int i=0; i < 2*k+1; i++) {
        product *= x;
    }
    return product;
}

long double sequence(long int k, long double x) {
    return pow2k1(x, k) / factorial2k1(k);
}


int main() {
    long double x;
    long int k;
    printf("Enter numbers x and k: ");
    scanf("%Lf %li", &x, &k);
    printf("%Lf", sequence(k, x));
    return 0;
}