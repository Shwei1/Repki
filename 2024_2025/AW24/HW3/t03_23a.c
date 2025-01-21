#include <stdio.h>
#include <math.h>

int onestep(double x) {
    if (x>=0) {
        return 1;
    }
    if (x<0) {
        return 0;
    }
}

int onestep_derivative(double x) {
    if (x != 0) {
        return 0;
    }
    else {
        printf("%lf\n", __DBL_MAX__);
    }
}

int main() {
    double x;
    int a;
    onestep_derivative(0);
    printf("Enter the value of x: ");
    scanf("%lf", &x);
    printf("Enter 1 to find onestep(x) or 2 to find d(onestep(x))/dx: ");
    scanf("%i", &a);
    if (a==1) {
        printf("%i", onestep(x));
    }
    else if (a==2) {
        printf("%i", onestep_derivative(x));
    }
    else {
        printf("No such function. Try again.");
    }

}