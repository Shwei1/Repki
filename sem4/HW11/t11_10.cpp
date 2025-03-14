#include <iostream>
#include <vector>
#include <set>

void find_possibles(int index, int left, int right, const std::vector<int>& plates, std::set<int>& valid_weights, int barbell) {
    if (index == plates.size()) { 
        if (left == right) {  
            valid_weights.insert(barbell + 2 * left);
        }
        return;
    }

    find_possibles(index + 1, left + plates[index], right, plates, valid_weights, barbell);

    find_possibles(index + 1, left, right + plates[index], plates, valid_weights, barbell);

    find_possibles(index + 1, left, right, plates, valid_weights, barbell);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> barbells(n);
    std::vector<int> plates(m);
    
    for (int i = 0; i < n; ++i) std::cin >> barbells[i];
    for (int i = 0; i < m; ++i) std::cin >> plates[i];

    std::set<int> results; 

    for (int barbell : barbells) {
        find_possibles(0, 0, 0, plates, results, barbell);
    }

    for (int weight : results) {
        std::cout << weight << std::endl;
    }

    return 0;
}
