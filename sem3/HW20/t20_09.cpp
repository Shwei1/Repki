#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>


void txt_to_bin(const std::string& txt_filename, const std::string& bin_filename){
    std::ifstream f_in(txt_filename);
    std::ofstream f_out(bin_filename);

    if (!f_in || !f_out){
        throw std::runtime_error("Could not open the file.");
    }
    std::string line;
    while (std::getline(f_in, line)){
        f_out.write(line.c_str(), (long)line.size());
        const char NEWLINE = '\n';
        f_out.write(&NEWLINE, sizeof('\n'));
    }

    f_in.close();
    f_out.close();
}

void read_bin(const std::string& filename, int& N, std::vector<double>& V0, std::vector<std::vector<double>>& V_i_n){
    std::ifstream f_in(filename, std::ios::binary);
    if (!f_in){
        throw std::runtime_error("Could not open the file");
    }

    std::string line;
    if (std::getline(f_in, line, '\n')){
        std::istringstream ss(line);
        double num;
        while(ss >> num){
            V0.push_back(num);
        }
    }

    if (std::getline(f_in, line, '\n')) {
        N = std::stoi(line);
    }

    for (int i = 0; i < N; ++i) {
        if (std::getline(f_in, line, '\n')) {
            std::istringstream iss(line);
            std::vector<double> row;
            int num;
            while (iss >> num) {
                row.push_back(num);
            }
           V_i_n.push_back(row);
        }
    }

    f_in.close();
}

int find_superset_count(std::vector<double>& V0, std::vector<std::vector<double>>& V_i_n){
    int superset_count = 0;
    std::sort(V0.begin(), V0.end());
    for (auto row: V_i_n){
        std::sort(row.begin(), row.end());
        if(std::includes(row.begin(), row.end(), V0.begin(), V0.end()))
            superset_count += 1;
    }
    return superset_count;
}




int main(){

    txt_to_bin("input2009.txt", "input2009.bin");

    std::vector<double> V0;
    int N;
    std::vector<std::vector<double>> V_i_n;

    read_bin("input2009.bin",N, V0, V_i_n);

    for (const auto& row: V_i_n){
        for (auto num: row){
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }

    int supersets = find_superset_count(V0, V_i_n);

    std::cout << "How many vectors from the file include the first vector as a subset: " << supersets << '\n';

}