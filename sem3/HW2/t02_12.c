#include <stdio.h>
#include <math.h>

int main()
{
    double r, h, V;
    printf("Enter the radius and the height of the cone: ");
    scanf("%lf %lf", &r, &h);
    V = 1.0/3 * M_PI * r * r * h;
    printf("%.3lf", V);
}