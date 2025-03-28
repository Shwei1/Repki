#include <iostream>
#include <stack>
#include <string>
using namespace std;

int n; 
int totalPairs; 

void generate(string expr, int openCount, int closeCount, stack<char>& stk) {

    if (expr.size() == n) {
        if (stk.empty())
            cout << expr << "\n";
        return;
    }

    if (openCount < totalPairs) {
        {
            expr.push_back('(');
            stk.push('(');
            generate(expr, openCount + 1, closeCount, stk);
            stk.pop();
            expr.pop_back();
        }
        {
            expr.push_back('[');
            stk.push('[');
            generate(expr, openCount + 1, closeCount, stk);
            stk.pop();
            expr.pop_back();
        }
    }

    if (!stk.empty() && closeCount < openCount) {
        char top = stk.top();
        if (top == '(') {
            expr.push_back(')');
            stk.pop();
            generate(expr, openCount, closeCount + 1, stk);
            stk.push('(');
            expr.pop_back();
        } else if (top == '[') {
            expr.push_back(']');
            stk.pop();
            generate(expr, openCount, closeCount + 1, stk);
            stk.push('[');
            expr.pop_back();
        }
    }
}

int main(){
    cin >> n;
    totalPairs = n / 2;
    stack<char> stk;
    generate("", 0, 0, stk);
    return 0;
}

