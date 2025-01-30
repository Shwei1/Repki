#include <stdio.h>
#include <math.h>

int main()
{
    long double a;
    printf("Enter your number: ");
    scanf("%Lf", &a);
    printf("Your number in 8th power is: %20.4Lf", powl(a, 8));
//    printf("%zu", sizeof(long double));
    return 0;
}
