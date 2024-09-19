#include <stdio.h>
#include <math.h>


long double series_pi(long double epsilon) {
    long int k = 0;
    long double result = 0.0, term;
    do {
        term = 1.0/powl(16,k) * (
                4.0/(8.0*k+1.0)
                -2.0/(8.0*k+4.0)
                -1.0/(8.0*k+5.0)
                -1.0/(8.0*k+6.0));
        result += term;
        k++;
    } while (term > epsilon);
    return result;
}

int main(){
    long double epsilon = 0.0001;
    printf("Enter the value of possible error: ");
    scanf("%Lf", &epsilon);
    printf("%Lf", series_pi(epsilon));
//printf("%Lf", sixteen_pow_k(2));
}
