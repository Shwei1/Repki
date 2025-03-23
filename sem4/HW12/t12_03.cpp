#include <iostream>
#include <memory>

#define STACK_MAX 100

class Stack {
private:
    std::size_t count;
    std::unique_ptr<int[]> container;
public:

    Stack(void){
        count = 0;
        container = std::make_unique<int[]>(STACK_MAX);
    }

    void push(int n){
        container[count++] = n;
        std::cout << "ok" << std::endl;
    }

    void pop(){
        if (count == 0){
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << container[--count] << std::endl;
    }

    void back(){
        if (count == 0){
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << container[count - 1] << std::endl;
    }

    void size(){
        std::cout << count << std::endl;
    }

    void clear(){
        count = 0;
        std::cout << "ok" << std::endl;
    }

};


int main(){
    std::string command;

    Stack stk = Stack();

    while(true){

        std::cin >> command;

        if (command == "push"){
            int n;
            std::cin >> n;
            stk.push(n);
        }
        else if (command == "pop"){
            stk.pop();
        }
        else if (command == "back"){
            stk.back();
        }
        else if (command == "size"){
            stk.size();
        }
        else if (command == "clear"){
            stk.clear();
        }
        else {
            std::cout << "bye" << std::endl;
            break;
        }
    }

    return 0;
}
