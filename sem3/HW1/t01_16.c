#include <stdio.h>
#include <math.h>

double ex2(double x) {
    return exp(-x * x);
}

int main() {
    char f_type;
    printf("Type the function you want to print out, 'a' for exp(-x^2), 'b' for sqrt(x): ");
    scanf("%c", &f_type);
    if (f_type == 'a') {
        printf("x----|-1-|-2-|-3-|-4-|-5-|\n-----|---|---|---|---|---|\nF(x)|-%.2lf-|-%.2lf-|-%.2lf-|-%.2lf-|-%.2lf-|\n",
               ex2(1), ex2(2), ex2(3), ex2(4), ex2(5));
    }
    else if(f_type == 'b'){
        printf("x----|-1-|-2-|-3-|-4-|-5-|\n-----|---|---|---|---|---|\nF(x)|-%.2lf-|-%.2lf-|-%.2lf-|-%.2lf-|-%.2lf-|\n",
               sqrt(1), sqrt(2), sqrt(3), sqrt(4), sqrt(5));
    }

}


