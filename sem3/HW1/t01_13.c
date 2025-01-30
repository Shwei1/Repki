#include <stdio.h>
#include <math.h>

int main() {
    double a;
    printf("Enter your number: ");
    scanf("%lf", &a);
    printf("log of your number is: %.3f", log10(a));
}