#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

unsigned long intersect_count(std::vector<std::string>& V1, std::vector<std::string>& V2, std::vector<std::string>& V3){
    std::sort(V1.begin(), V1.end(), [](const std::string& a, const std::string& b)->bool {
        return a.length() < b.length();});

    std::sort(V2.begin(), V2.end(), [](const std::string& a, const std::string& b)->bool {
        return a.length() < b.length();});

    V3.resize(V1.size() + V2.size());

    auto it = std::set_union(V1.begin(), V1.end(), V2.begin(), V2.end(), V3.begin(), [](const std::string& a, const std::string& b)->bool {
        return a.length() < b.length();});

    V3.resize(it - V3.begin());

    std::sort(V3.begin(), V3.end(), [](const std::string& a, const std::string& b)->bool {
        return a.length() > b.length();});

    return V3.size();
}


int main(){

    std::vector<std::string> V1;
    std::vector<std::string> V2;

    std::string line;
    std::cout << "Enter the first vector (enter an empty line to finish):\n";
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        V1.push_back(line);
    }

    std::cout << "Enter the second vector (enter an empty line to finish):\n";
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        V2.push_back(line);
    }

    std::vector<std::string> intersection;

    std::cout << "Amount of elements that are at least in one vector: " << intersect_count(V1, V2, intersection) << '\n';
    std::cout << "Shared elements:\n";
    for (const auto& word: intersection){
        std::cout << word << ' ';
    }
}