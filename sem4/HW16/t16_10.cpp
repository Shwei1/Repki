#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

struct Node {
    int id;
    Node* parent;
    std::vector<Node*> children;
};

/*  Тут імплементується тупий перебір по всіх модифікаціях. Суть така:
    ізоморфізм дерев показуємо через зведення до канонічного виду, тобто
    строки дужок. Далі для кожної модифікації співставляємо її канонічний
    вигляд до порядкового номера модифікації. Після кожної модифікації
    перевіряємо наявність в таблиці, і якщо ізоморфна вже була, виводимо,
    на якому порядковому номері була. Проходить більш ніж на половину, інше
    по часу надто повільно, але я вважаю це вже перемога.
*/

std::string encode(Node* node) {
    std::string s = "(";
    for (Node* child : node->children) {
        s += encode(child);
    }
    s += ")";
    return s;
}

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<Node*> nodes(N + 1, nullptr);
    for (int i = 1; i <= N; i++){
        nodes[i] = new Node{i, nullptr, {}};
    }

    for (int i = 1; i <= N; i++){
        int K;
        std::cin >> K;
        for (int j = 0; j < K; j++){
            int child_id;
            std::cin >> child_id;
            nodes[i]->children.push_back(nodes[child_id]);
            nodes[child_id]->parent = nodes[i];
        }
    }

    std::unordered_map<std::string,int> table;
    table.reserve(M + 1);

    std::string s0 = encode(nodes[1]);
    table[s0] = 0;

    for (int j = 1; j <= M; j++){
        int S, F;
        std::cin >> S >> F;
        Node* snode = nodes[S];
        Node* fnode = nodes[F];
        Node* parent = snode->parent;

        auto& siblings = parent->children;
        siblings.erase(std::remove(siblings.begin(), siblings.end(), snode), siblings.end());

        fnode->children.push_back(snode);
        snode->parent = fnode;

        std::string sj = encode(nodes[1]);

        if (table.find(sj) != table.end()){
            std::cout << table[sj] << " " << j << std::endl;
            return 0;
        }
    
        table[sj] = j;
    }

    std::cout << -1 << std::endl;

    for (int i = 1; i <= N; i++){
        delete nodes[i];
    }

    return 0;
}

