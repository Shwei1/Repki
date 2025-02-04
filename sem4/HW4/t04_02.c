#include <stdio.h>
#include <math.h>

double func(double x){
    return x * x + sqrt(x);
}

double solution(double C){
    double right = fmax(1l, C);
    double left = 0l;
    double epsilon = 1e-6;
    int counter = 0; 
    while(1){
        counter++;
        double m = (right + left)/2;
        double result = func(m);
        if (fabs(result - C) < epsilon){
            return m;
    }
        else if (result > C){
            right = m;
        }
        else{
            left = m;
        }
    }
}



int main(){
    double C;
    scanf("%lf", &C);
    printf("%lf", solution(C));
    return 0;
}
