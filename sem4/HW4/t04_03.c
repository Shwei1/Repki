#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double result(double x){
    return x * x * x + x + 1;
}

double real_search(double left, double right){
    double epsilon = 1e-15;
    double return_value = -1.0;
    while(right - left > epsilon){
        double m = (left + right)/2.0;
        if (result(m) > 5){
            return_value = m;
            right = m;
        }
        else
            left = m;
    }

    return return_value;
}

int main(){
   clock_t current;
   double spent;
   double res = real_search(0.0, 10.0);
   current = clock();
   spent = (double) (clock() - current) / CLOCKS_PER_SEC;
   printf("The smallest x that satisfies x^3+x+1>5 is %0.14lf.\nIt took %lf seconds.\n", res, spent); // 1.3787967001295
   return 0;

}
