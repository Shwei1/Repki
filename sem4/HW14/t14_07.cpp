#include <deque>
#include <iostream>


int main(void){
    std::deque<int> player1;
    std::deque<int> player2;
    int n;
    std::cin >> n;

    for (int i = 0; i < int(n/2); i++){
        int item;
        std::cin >> item;
        player1.push_back(item);
    }

    for (int i = 0; i < int(n/2); i++){
        int item;
        std::cin >> item;
        player2.push_back(item);
    }

    int counter = 0;
    while (counter < 2 * 100000){
        if (player1.empty()){
            std::cout << "second " << counter << std::endl;
            return 0;
        }
        else if (player2.empty()){
            std::cout << "first " << counter << std::endl;
            return 0;
        }

        int card1 = player1.front();
        int card2 = player2.front();

        if (card1 == 0 && card2 == n-1){
            player2.pop_front();
            player1.pop_front();
            player1.push_back(card1);
            player1.push_back(card2);
        }
        else if (card2 == 0 && card1 == n-1){
            player2.pop_front();
            player1.pop_front();
            player2.push_back(card1);
            player2.push_back(card2);
        }
        else {
            if (card1 > card2){
                player2.pop_front();
                player1.pop_front();
                player1.push_back(card1);
                player1.push_back(card2);
            }
            else {
                player1.pop_front();
                player2.pop_front();
                player2.push_back(card1);
                player2.push_back(card2);
            }
        }
        counter++;
    }

    std::cout << "draw" << std::endl;
    return 0;
}

