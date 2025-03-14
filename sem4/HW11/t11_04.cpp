#include <iostream>
#include <string>
#include <gmp.h>

void karatsuba(mpz_t result, mpz_t num1, mpz_t num2){

    if (mpz_sizeinbase(num1, 10) < 40 || mpz_sizeinbase(num2, 10) < 40) {
        mpz_mul(result, num1, num2); 
        return;
    }

    std::size_t size1 = mpz_sizeinbase(num1, 10);
    std::size_t size2 = mpz_sizeinbase(num2, 10);

    std::size_t max = size1 > size2 ? size1 : size2;
    std::size_t max2 = max / 2;

    mpz_t base, high1, low1, high2, low2, sum1, sum2, z0, z1, z2, temp1, temp2;
    mpz_inits(base, high1, low1, high2, low2, sum1, sum2, z0, z1, z2, temp1, temp2, NULL);

    mpz_ui_pow_ui(base, 10, max2);

    mpz_tdiv_q(high1, num1, base);
    mpz_tdiv_r(low1, num1, base);

    mpz_tdiv_q(high2, num2, base);
    mpz_tdiv_r(low2, num2, base);

    karatsuba(z0, low1, low2);

    karatsuba(z2, high1, high2);

    mpz_add(sum1, low1, high1);  
    mpz_add(sum2, low2, high2); 
    karatsuba(z1, sum1, sum2);

    mpz_sub(z1, z1, z2);
    mpz_sub(z1, z1, z0);

    mpz_mul(temp1, z2, base);    
    mpz_mul(temp1, temp1, base);

    mpz_mul(temp2, z1, base);

    mpz_add(result, temp1, temp2); 
    mpz_add(result, result, z0);

    mpz_clears(base, high1, low1, high2, low2, sum1, sum2, z0, z1, z2, temp1, temp2, NULL);
}


int main(int argc, char *argv[]){

    char buffer1[262144];
    char buffer2[262144];

    std::cin >> buffer1 >> buffer2;

    mpz_t num1, num2;
    mpz_init(num1);
    mpz_init(num2);

    mpz_set_str(num1, buffer1, 10);
    mpz_set_str(num2, buffer2, 10);

    mpz_t result;
    mpz_init(result);

    karatsuba(result, num1, num2);

    gmp_printf("%Zd\n", result);

    mpz_clear(num1);
    mpz_clear(num2);
    mpz_clear(result);
}
