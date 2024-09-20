#include <stdio.h>

int main() {
    unsigned int x = 1; // 01101100
    unsigned long k = 0;
    printf("%sEnter your natural number: %s", "\033[33m", "\033[0m" );
    scanf("%u", &x);
    int condition;
    switch (x) {
        case 0:
            printf("One bit does not exist.\n");
            printf("No zero-bit as one-bit does not exist.\n");
            break;
        case 1:
            printf("Index of the first one-bit is 1.\n");
            printf("No zero-bit.");
            break;
        case 2:
            printf("Index of the first one-bit is 2.\n");
            printf("Index of the first zero-bit after the first one-bit is 1.\n");
            break;
        default:
            do {
                k++;
                condition = ((x << k) >> k) == x;
//                if (k > 33) {
//                    printf("No one-bit.\n");
//                    condition = 0;
//                }

            } while (condition);
            if (x > 2) {
                printf("Index of the first one-bit is %li.\n", sizeof(int) * 8 - k + 1);
            } else if (x == 1) {
                printf("1\n");
            } else if (x == 2) {
                printf("2\n");
            }
            x = ~x;
            x = (x << k) >> k;
            k = k - 1;
            do {
                k++;
                condition = ((x << k) >> k) == x;
                if (k > 32) {
                    printf("No zero-bit.\n");
                    condition = 0;
                }
            } while (condition);

            if (x > 2) {
                printf("Index of the first zero-bit after the first one-bit is %li.\n", sizeof(int) * 8 - k + 1);
            }
    }

}