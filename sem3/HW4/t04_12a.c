#include <stdio.h>

unsigned int p_2(unsigned int n) {
    return 1U << n;
}

long double xpow(long double x, unsigned int n) {
    unsigned int p = p_2(n);
    long double result = 1;
    for (int i=1; i<=p; i++) {
        result *= x;
    }
    return result;
}

long double polynom(long double x, unsigned int n) {
    long double result = 0;
    for (int i=0; i <= n; i++) {
        result += xpow(x, i);
    }
    return result + p_2(0);
}

int main() {
    unsigned int n;
    long double x;
    printf("Enter the values of x and n to compute\n[x^(2^n)+x^(2^n-1)+...+x^2+1]:\n");
    scanf("%Lf %u", &x, &n);
    printf("The result is %Lf", polynom(x, n));

}
