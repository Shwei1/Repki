#include <iostream>
#include <stack>
#include <vector>

bool check (const std::vector<int>& wagons){
    std::stack<int> station;
    int pushed_count = 0;
    int incoming = 1;
    bool arrived = false;

    while (pushed_count < wagons.size()){
        //std::cout << "Incoming wagon No. " << incoming << std::endl;
        //std::cout << "Succeeded to be pushed to B so far: " << pushed_count << std::endl;
        if (!station.empty() && wagons[pushed_count] == station.top()){
            station.pop();
            pushed_count++;
        }
        else if (!arrived){
            station.push(incoming++);
            if (incoming > wagons.size()){ arrived = true;}
        }
        else {
            return false;
        }
    }
    return true;
}


int main(void){
    
    while(true){

        int n; 
        std::cin >> n;

        if (n == 0){
            break;
        }

        while(true){
            std::vector<int> wagons(n);
            for (int i = 0; i < n; i++){
                std::cin >> wagons[i];
                if (wagons[i] == 0) break;
            }

            if (wagons[0] == 0) break;

            if (check(wagons))
                std::cout << "Yes" << std::endl;
            else 
                std::cout << "No" << std::endl;

        }
        std::cout << "\n";
    }
    return 0;
}
