#include <stdio.h>
#include <math.h>

long double sixteen_pow_k(long int k) {
    long int product = 1;
    for (int i=0; i < k; i++) {
        product *= 16;
    }
    return product;
}

long int negone_pow_k(long int k) {
    if (k & 1) {
        return -1;
    }
    else {
        return 1;
    }

}
long double series_pi(long double epsilon) {
    long int k = 0;
    long double result = 0;
    while (M_PI - (result * 0.5) > epsilon) {
        result += negone_pow_k(k) / sixteen_pow_k(k) * (8/(8*(long double)k+2)+4/(8*(long double)k+3)+4/(8*(long double)k+4)-(1/(8*(long double)k+7)));
        k++;
    }
    return result * 0.5;
}

int main(){
    long double epsilon = 0.0001;
    printf("Enter the value of possible error: ");
    scanf("%Lf", &epsilon);
    printf("%Lf", series_pi(epsilon));
//printf("%Lf", sixteen_pow_k(2));
}
