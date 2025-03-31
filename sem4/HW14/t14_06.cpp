#include <iostream>
#include <string>

struct Node {
    int value;
    Node *next;
    Node *previous;
};

class Queue {
private:
    Node *head;
    Node *tail;
    std::size_t size;
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        clear();
    }

    void push_front(int n) {
        std::cout << "ok" << std::endl;
        Node *node = new Node;
        node->value = n;
        node->previous = nullptr;
        node->next = head;
        
        if (head != nullptr) {
            head->previous = node;
        }
        head = node;
        
        if (tail == nullptr) {
            tail = node;
        }
        ++size;
    }

    void push_back(int n) {
        std::cout << "ok" << std::endl;
        Node *node = new Node;
        node->value = n;
        node->next = nullptr;
        node->previous = tail;
        
        if (tail != nullptr) {
            tail->next = node;
        }
        tail = node;
        
        if (head == nullptr) {
            head = node;
        }
        ++size;
    }

    void pop_front() {
        if (!head) {
            std::cout << "error" << std::endl;
            return;
        }

        std::cout << head->value << std::endl;
        Node *temp = head;
        head = head->next;
        if (head) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --size;
    }

    void pop_back() {
        if (!tail) {
            std::cout << "error" << std::endl;
            return;
        }

        std::cout << tail->value << std::endl;
        Node *temp = tail;
        tail = tail->previous;

        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --size;
    }

    void front() {
        if (!head) {
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << head->value << std::endl;
    }

    void back() {
        if (!tail) {
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << tail->value << std::endl;
    }

    void _size() {
        std::cout << size << std::endl;
    }

    void clear() {
        Node *curr = head;
        while (curr) {
            Node *temp = curr->next;
            delete curr;
            curr = temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

int main() {
    std::string cmd;
    Queue q;
    
    while (std::cin >> cmd) {
        if (cmd == "push_back") {
            int n;
            std::cin >> n;
            q.push_back(n);
        }
        else if (cmd == "push_front") {
            int n;
            std::cin >> n;
            q.push_front(n);
        }
        else if (cmd == "pop_front") {
            q.pop_front();
        }
        else if (cmd == "pop_back") {
            q.pop_back();
        }
        else if (cmd == "front") {
            q.front();
        }
        else if (cmd == "back") {
            q.back();
        }
        else if (cmd == "size") {
            q._size();
        }
        else if (cmd == "clear") {
            q.clear();
            std::cout << "ok" << std::endl;
        }
        else {
            std::cout << "bye" << std::endl;
            break;
        }
    }
    return 0;
}

