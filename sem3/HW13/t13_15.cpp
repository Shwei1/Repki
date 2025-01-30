#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

int charcount(std::string const &str, char c){
    std::istringstream stream(str);
    std::string temp;
    int counter = 0;
    while (stream >> temp){
        if(temp.find(c) != std::string::npos){
            counter += 1;
        }
    }
    return counter;
}

int main(){
    std::string str;
    getline(std::cin, str);
    char ch;
    std::cin >> ch;
    std::cout << charcount(str, ch) << '\n';
    return 0;
}