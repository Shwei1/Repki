#include <stdio.h>

int main(){
    unsigned m1;
    unsigned k1;
    unsigned long long m2;
    unsigned long long k2;
    int p;
    printf("Enter data type: 1 for unsigned, 2 for long long unsigned: ");
    scanf("%i", &p);
    printf("Enter the value of m and k: ");
    if (p==1) {
        scanf("%u %u", &m1, &k1);
        m1 = (m1 >> k1) << k1;
        m1 = (m1 << k1) >> k1;
        printf("Your number in decimal is %u and %o in octal", m1, m1);
    }
    else if (p==2) {
        scanf("%llu %llu", &m2, &k2);
        m2 = (m2 >> k2) << k2;
        m2 = (m2 << k2) >> k2;
        printf("Your number in decimal is %llu and %llo in octal", m2, m2);
    }
    else {
        printf("%sUnknown parameter. Try again.%s", "\033[31m", "\033[31m");
    }

}