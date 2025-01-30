#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#define SPACE ' '

bool check_integer(const std::string &str){
    std::istringstream ss(str);
    int num;
    char c;
    return (ss >> num) && !(ss >> c);
}

std::string read_from_file(const std::string &file){
    std::ifstream f(file);
    std::ostringstream ss_content;
    ss_content << f.rdbuf();
    return ss_content.str();
}

void int_to_bin_file(const std::string &file){
    std::string content = read_from_file(file);
    std::ofstream f(file, std::ios::out | std::ios::trunc);
    f.close();
    std::ofstream rf(file, std::ios::out);
    std::string word;
    std::istringstream ss(content);
    while (ss >> word){
        if(check_integer(word)){
            int n = stoi(word);
            std::bitset<8> binary(n);
            rf << binary << SPACE;
        }
        else {
            rf << word << SPACE;
        }
    }
    rf.close();
}

int main(){
    int_to_bin_file("input1415.txt");
}
