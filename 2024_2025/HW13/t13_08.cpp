#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

std::string clean(std::string const &str){
    std::istringstream stream(str);
    std::string newstr;
    std::string temp;
    char space;
    while (stream >> temp){
        char last = temp.back();
        temp.erase(std::remove(temp.begin(), temp.end(), last), temp.end());
        newstr += temp;
        if (stream.get(space) && space == ' '){
            newstr += space;
        }
        int space_count = 0;

        while (stream.get(space) && space == ' ') {
            newstr += space;
            space_count++;
        }

        if (space_count == 0) break;

        if (stream.eof()) {
            break;
        }

        if (stream) {
            stream.unget();
        }

    }

    newstr.erase(newstr.find_last_not_of(' ') + 1);

    return newstr;

}

int main(){
    std::string s;
    getline(std::cin, s);
    clean(s);
    std::cout << clean(s) << '\n';
    return 0;
}