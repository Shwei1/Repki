#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

struct node{
    std::string value;
    int pr;

    node(std::string val, int priority): value(std::move(val)), pr(priority){}
};

class pqueue{
private:
    std::vector<node> arr;

    void sift_up(std::size_t idx) {
        while (idx > 1) {
            std::size_t parent = idx / 2;
            if (arr[idx].pr > arr[parent].pr) {
                std::swap(arr[idx], arr[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(std::size_t idx) {
        std::size_t n = arr.size() - 1;
        while (true) {
            std::size_t left    = 2 * idx;
            std::size_t right   = left + 1;
            std::size_t smallest = idx;

            if (left  <= n && arr[left].pr > arr[smallest].pr) smallest = left;
            if (right <= n && arr[right].pr > arr[smallest].pr) smallest = right;

            if (smallest != idx) {
                std::swap(arr[idx], arr[smallest]);
                idx = smallest;     
            } else {
                break;
            }
        }
    }

public:

    explicit pqueue(void){
        arr.emplace_back("", 0);
    }

    bool empty(void){
        return arr.size() <= 1;
    }

    std::size_t size() const {
        return arr.size() > 0 ? arr.size() - 1 : 0;
    }

    void add(const std::string& val, int priority){
        arr.emplace_back(val, priority);
        sift_up(arr.size() - 1);
    }

    void pop() {
        node top = arr[1];
        arr[1] = std::move(arr.back());
        arr.pop_back();  
        sift_down(1);
        std::cout << top.value << ' ' << top.pr << std::endl;
    }

    void change(const std::string& val, int new_priority) {
        auto it = std::find_if(
            arr.begin() + 1, arr.end(),
            [&](const node& n){ return n.value == val; }
        );

        std::size_t idx = std::distance(arr.begin(), it);

        int old_priority = it->pr;
        it->pr = new_priority;

        if (new_priority > old_priority) {
            sift_up(idx);
        } else if (new_priority < old_priority) {
            sift_down(idx);
        }
    }

};

int main() {
    pqueue pq;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "ADD"){
            std::string value;
            int priority;
            iss >> value >> priority;
            pq.add(value, priority);
        }
        if (cmd == "CHANGE"){
            std::string value;
            int priority;
            iss >> value >> priority;
            pq.change(value, priority);
        }
        if (cmd == "POP"){
            pq.pop();
        }
    }

    return 0;
}
