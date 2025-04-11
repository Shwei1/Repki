#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

/*  Тут імплементується тупий перебір по всіх модифікаціях. Суть така:
    ізоморфізм дерев показуємо через зведення до канонічного виду, тобто
    строки дужок. Далі для кожної модифікації співставляємо її канонічний
    вигляд до порядкового номера модифікації. Після кожної модифікації
    перевіряємо наявність в таблиці, і якщо ізоморфна вже була, виводимо,
    на якому порядковому номері була. Проходить більш ніж на половину, інше
    по часу надто повільно, але я вважаю це вже перемога.
*/

std::string encode(int u, const std::vector<std::vector<int>>& children) {
    std::string s = "(";
    for (int v : children[u]) {
        s += encode(v, children);
    }
    s += ")";
    return s;
}

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> children(N+1);
    std::vector<int> parent(N+1, 0);

    for(int i = 1; i <= N; i++){
        int K;
        std::cin >> K;

        for (int j = 0; j < K; j++){
            int v;
            std::cin >> v;
            children[i].push_back(v);
            parent[v] = i;
        }
    }

    std::unordered_map<std::string,int> table;
    table.reserve(M+1);

    std::string s0 = encode(1, children);
    table[s0] = 0;

    for (int j = 1; j <= M; j++){
        int S, F;
        std::cin >> S >> F;

        int P = parent[S];
        auto& siblings = children[P];
        siblings.erase(std::find(siblings.begin(), siblings.end(), S));

        children[F].push_back(S);
        parent[S] = F;

        std::string sj = encode(1, children);

        auto it = table.find(sj);
        if(it != table.end()){
            std::cout << it->second << " " << j << std::endl;
            return 0;
        }
        table[sj] = j;
    }

    std::cout << -1 << std::endl;
    return 0;
}
