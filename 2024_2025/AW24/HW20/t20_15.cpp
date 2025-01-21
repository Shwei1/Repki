#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

std::map<char, unsigned long> find_letters(const std::vector<std::string>& vect){
    std::map<char, unsigned long> M;
    for (auto word: vect){
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::tolower(c);});
        M[word[0]] += word.length();
    }
    return M;
}


int main(){
    std::vector<std::string> V;
    std::cout << "Enter your vector:\n ";
    std::string word;
    while(std::getline(std::cin, word)){
        if (word.empty())
            break;
        V.push_back(word);
    }

    std::map<char, unsigned long> M = find_letters(V);

    for (auto [key, value]: M){
        std::cout << key << ": " << value << std::endl;
    }

}