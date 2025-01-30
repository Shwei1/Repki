#include <stdio.h>

long int seq(long int n) {
    if (n == 0 || n == 1 || n == 2) {
        return 1;
    }
    else {
        return (n+4)*(seq(n-1)-1)+(n+5)*seq(n-3);
    }
}

int main() {
    long int n;
    printf("Enter the number of term: ");
    scanf("%li", &n);
    printf("The term is equal to %li", seq(n));
}