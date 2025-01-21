#include <iostream>
#include <fstream>

void partition_file(const std::string &filename){
    std::ifstream Ff(filename);
    std::ofstream Hf("H.txt");
    std::ofstream Gf("G.txt");
    std::string line;
    while (std::getline(Ff, line)){
        if (line.length() % 2 == 0)
            Gf << line << std::endl;
        else
            Hf << line << std::endl;
    }
    Ff.close();
    Hf.close();
    Gf.close();
}

int main(){
    partition_file("F.txt");
}