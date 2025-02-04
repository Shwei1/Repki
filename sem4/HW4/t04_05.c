#include <stdio.h>
#include <math.h>

double evaluate(double x){
    return x * x * x + 4.0 * x * x + x - 6;
}

double real_search(double left, double right){
    double epsilon = 1e-15;
    while(fabs(left - right) > epsilon){
        double m = (left + right) / 2;
        if (fabs(evaluate(m)) < epsilon)
           return m;
        else if (evaluate(m) * evaluate(left) < 0)
            right = m;
        else
            left = m;
    }
    return left;
}

int main(void){
    printf("The solution to equation x^3+4x^2+x-6 in [0, 2] is %0.14lf.\n", real_search(0.0, 2.0)); // 1.00000000000000

    return 0;
}
