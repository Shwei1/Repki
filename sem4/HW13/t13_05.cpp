#include <stack>
#include <iostream>
#include <string>

void check(const std::string& str){
    std::stack<char> stk;

    for (char c: str){
       // std::cout << c << ' ' << stk.size() << std::endl;
        switch (c){
            case '(':
                stk.push(')');
                break;
            case '[':
                stk.push(']');
                break;
            case '{':
                stk.push('}');
                break;
            case ']':
            case ')':
            case '}':
                if (stk.empty() || stk.top() != c) {
                    std::cout << "no" << std::endl;
                    return;
                }
                    stk.pop();
                    break;
            default:
                break;
        }
    }

    std::cout << (stk.empty() ? "yes" : "no") << std::endl;
    return;
}


int main(){
    std::string sequence;

    std::getline(std::cin, sequence);

    check(sequence);

    return 0;
}
