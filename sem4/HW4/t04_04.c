#include <stdio.h>
#include <math.h>

double evaluate(double x){
    return sin(x) - x/3;

}

double real_search(double left, double right){
    double epsilon = 1e-15;
    while(fabs(left-right) > epsilon){
        double m = (right + left) / 2;
        if (fabs(evaluate(m)) < epsilon){
            return m;
        }
        if (evaluate(m) * evaluate(left) < 0)
            right = m;
        else 
            left = m;
    }
    return -1.0;
}

int main(){

    printf("The solution to sin(x)=x/3 on [1.6, 3] is %0.14lf.\n", real_search(1.6, 3.0)); // 2.27886266007583.

    return 0;
}
