#include <stdio.h>
#include <math.h>

double bent(double x) {
    return (sqrt(x * x + 1) - 1)/2 + x;
}

double bent_derivative(double x) {
    return x/(2*sqrt(x*x + 1)) + 1;
}

int main() {
    double a;
    printf("Enter the number for the bent function and its derivative: ");
    scanf("%lf", &a);
    printf("The bent of your number is %lf and the derivative at that point is %lf"
           , bent(a), bent_derivative(a));
    return 0;
}
