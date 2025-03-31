#include <iostream>
#include <string>
#include <array>

struct Node{
    int value;
    Node *next;
};

class queue{
private:
    Node *head;
    Node *tail;
    std::size_t size;
public:
    queue(){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    void push(int n){
            std::cout << "ok" << std::endl;
            Node *node = new Node;
            node->value = n;
            node->next = nullptr;
            size++;

        if (!head){
            head = tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    void pop(){
        if (!size){
            std::cout << "error" << std::endl;
            return;
        }
        size--;
        Node *temp = head;
        head = head->next;
        std::cout << temp->value << std::endl;
        delete temp;
        if (!head) { 
            tail = nullptr;
        }
    }

    void front(){
       if (!size){
            std::cout << "error" << std::endl;
            return;
        }

        std::cout << head->value << std::endl; 
    }

    void _size(){
        std::cout << size << std::endl;
    }

    void clear(){
        Node *curr = head;
        while (curr){
            Node *temp = curr->next;
            delete curr;
            curr = temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;

        std::cout << "ok" << std::endl;
    }
};

int main(void){
    std::string cmd;

    queue q = queue();
    
    while(true){
        std::cin >> cmd;
        if (cmd == "push"){
            int n;
            std::cin >> n;
            q.push(n);
        }
        else if (cmd == "pop"){
            q.pop();
        }
        else if (cmd == "front"){
            q.front();
        }
        else if (cmd == "size"){
            q._size();
        }
        else if (cmd == "clear"){
            q.clear();
        }
        else {
            std::cout << "bye" << std::endl;
            break;
        }
    }
    return 0;
}

