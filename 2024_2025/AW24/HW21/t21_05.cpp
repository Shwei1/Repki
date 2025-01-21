#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>

int main(){

    std::string word;
    std::cin >> word;

    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::toupper(c);});

    std::cout << word << std::endl;
}