#include <stdio.h>
#include <math.h>

double module(double x) {
    if (x <= 0) {
        return -1 * x;
    }
    else {
        return x;
    }
}

double double_module(double x) {
    return module(module(x) - 1) - 1;
}

int signum(double x) {
    if (x < 0) {
        return -1;
    }
    else if (x > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

double sine_module(double x) {
    return sin(module(x));
}


int main(){
    double x;
    char f;
    printf("Enter your number: ");
    scanf("%lf", &x);
    printf("Enter the function you want to use:\n'a' for |x|\n'b' for ||x|-1|-1\n'c' for sign(x)\n'd' for sin(|x|)\n");
    scanf(" %c", &f);
    switch (f) {
        case 'a':
            printf("%.3lf\n", module(x));
            break;
        case 'b':
            printf("%.3lf", double_module(x));
            break;
        case 'c':
            printf("%i", signum(x));
            break;
        case 'd':
            printf("%.3lf", sine_module(x));
            break;
        default:
            printf("Unknown function. Try again");
            break;

    }

}