#include <stack>
#include <string>
#include <iostream>

bool is_operator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void translate(const std::string& expression) {

    struct Expr {
        std::string expr;
        int prec; 
    };
    
    auto get_precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0; 
    };
    
    std::stack<Expr> stk;
    
    for (int i = expression.size() - 1; i >= 0; i--) {
        char c = expression[i];
        
        if (!is_operator(c)) {
            stk.push({std::string(1, c), 3});
        } else {
            int cur_prec = get_precedence(c);
            
            Expr left = stk.top(); stk.pop();
            Expr right = stk.top(); stk.pop();
            
            std::string left_Expr = left.expr;
            if (left.prec < cur_prec) {
                left_Expr = "(" + left_Expr + ")";
            }
            
            std::string right_Expr = right.expr;
            if (right.prec < cur_prec || ((c == '-' || c == '/') && right.prec == cur_prec)) {
                right_Expr = "(" + right_Expr + ")";
            }
            
            std::string combined = left_Expr + c + right_Expr;
            stk.push({combined, cur_prec});
        }
    }
    
    std::cout << stk.top().expr << std::endl;
}



int main(){
    std::string buffer;

    std::getline(std::cin, buffer);

    translate(buffer);

    return 0;
}

