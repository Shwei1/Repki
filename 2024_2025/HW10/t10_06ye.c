#include <stdio.h>
#include <math.h>

typedef struct Circle{
    double r;
    struct{
        double x;
        double y;
    } centre;
} Circle;

void output(Circle c){
    printf("Circulus cum radio \033[33m%lf\033[0m et coordinatis centri \033[34m(%lf, %lf)\033[0m\n", c.r, c.centre.x, c.centre.y);
}

double area(Circle c){
    return c.r * c.r * M_PI;
}

double circumference(Circle c){
    return 2 * M_PI * c.r;
}

int main(){
    Circle c;
    printf("Scribe radium circuli tui: ");
    scanf("%lf", &c.r);
    printf("Scribe coordinatas centri circuli tui: ");
    scanf("%lf %lf", &c.centre.x, &c.centre.y);
    output(c);
    printf("Area circuli est \033[33m%lf\033[0m\n", area(c));
    printf("Circumferentia circuli est \033[33m%lf\033[0m\n", circumference(c));

}
