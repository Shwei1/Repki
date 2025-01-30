#include <stdio.h>

int main() {
    long double T = 365 + 1.0/(4+1.0/(7+1.0/1+1.0/3));
    printf("%Lf", T);
}