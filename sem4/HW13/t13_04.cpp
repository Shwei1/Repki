#include <iostream>
#include <stack>
#include <string>
#include <gmp.h>

void translate(mpz_t A, mpz_t P){
    std::stack<std::string> stk;

    if (mpz_cmp_ui(A, 0u) == 0){
        std::cout << "0" << std::endl;
        return;
    }

    std::string RES = "";
    mpz_t TEMP;
    mpz_init(TEMP);
    mpz_set(TEMP, A);

    while (mpz_cmp_ui(TEMP, 0) > 0){
        mpz_t LAST_DIGIT;
        mpz_init(LAST_DIGIT);

        mpz_mod(LAST_DIGIT, TEMP, P);

        mpz_tdiv_q(TEMP, TEMP, P);

        char *tmp = mpz_get_str(NULL, 10, LAST_DIGIT);
        std::string LAST_DIGIT_STR = tmp;
        free(tmp);

        if (mpz_cmp_ui(LAST_DIGIT, 9) > 0) {
            LAST_DIGIT_STR = "[" + LAST_DIGIT_STR + "]";
        }

        stk.push(LAST_DIGIT_STR);

        mpz_clear(LAST_DIGIT);
    }

    while (!stk.empty()) {
        RES += stk.top();
        stk.pop();
    }

    std::cout << RES << std::endl;

    mpz_clear(TEMP);
}


int main(){

    char buffer1[1001];
    char buffer2[1001];

    std::cin >> buffer1;
    std::cin >> buffer2;

    mpz_t A, P;
    mpz_inits(A, P, NULL);

    mpz_set_str(A, buffer1, 10);
    mpz_set_str(P, buffer2, 10);

    translate(A, P);

    mpz_clears(A, P, NULL);

    return 0;
}
