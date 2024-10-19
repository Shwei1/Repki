#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
//#define N 1000


int main(){
    std::ifstream f_in("input1206.txt");
    std::ofstream f_out("output1206.txt");
    if (!f_in) {
        std::cerr << "Oops, problems with the file" << std::endl;
        return 1;
    }

    double num;
    while(f_in >> num){
        f_in.ignore(1, ',');
        double chunya = log(num);
        if (isnan(chunya) or isinf(chunya)){
            f_out << "log of " << num << " is undefined." << std::endl;
        }
        else
            f_out << "log of " << num << " is "  << std::setprecision(5) << chunya << std::scientific <<
            " or " << chunya << std::defaultfloat << std::endl;

    }













    f_in.close();
    f_out.close();
}