#include <stdio.h>
#include <math.h>

double a_k(int, double, double);
double b_k(int, double, double);

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double a_k(int k, double u, double v) {
    if (k == 1) {
        return u;
    }
    else {
        return 2 * b_k(k, u, v) + a_k(k-1, u, v);
    }
}

double b_k(int k, double u, double v) {
    if (k == 1) {
        return v;
    }
    else {
        return 2 * pow(a_k(k-1, u, v), 2) + b_k(k-1, u, v);
    }
}

double seq(long int n, double u, double v) {
    double result = 0, term;
   for (int k = 1; k <= n; k++) {
       term = a_k(k, u, v) * b_k(k, u, v) / factorial(k+1);
       result += term;
   }
   return result;
}


int main(){
    long int n;
    double u, v;
    printf("%lf", seq(8, 1, 1));
}






