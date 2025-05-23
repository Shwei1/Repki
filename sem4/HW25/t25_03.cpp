#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <utility>

static constexpr int INF = std::numeric_limits<int>::max();

class PQueue {
private:
    std::vector<std::pair<int, int>> heap;
    std::unordered_map<int, std::size_t> elements;
public:
    std::size_t size;

    PQueue(void){
        heap.push_back({0, 0});
        size = 0;
    }

    bool empty(void){
        return size == 0;
    }

    void insert(int key, int weight) {
        if (elements.count(key)) {
            change(key, weight); 
            return;
        }

        heap.push_back({key, weight});
        size++;
        elements[key] = size;
        siftUp();
    }

    std::pair<int, int> pop_min(void){
        auto root = heap[1];

        swap(1, size);
        heap.pop_back();
        elements.erase(root.first);
        size--;

        siftDown();

        return root;
    }

    void swap(std::size_t i, std::size_t j){
        std::size_t pos_i = heap[i].first;
        std::size_t pos_j = heap[j].first;
        elements[pos_i] = j;
        elements[pos_j] = i;

        auto temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void siftDown(void){
        std::size_t i = 1;
        while (2 * i <= size){
            std::size_t left = 2 * i;
            std::size_t right = left + 1;
            std::size_t min_child = left;

            if (right <= size && heap[right].second < heap[left].second)
                min_child = right;

            if (heap[i].second > heap[min_child].second)
                swap(i, min_child);
            else 
                break;
            
            i = min_child;    
        }
    }

    void siftUp(void){
        std::size_t i = size;
        while (i > 1) {
            std::size_t parent = i / 2;
            if (heap[i].second < heap[parent].second)
                swap(i, parent);
            else    
                break;
            
            i = parent;
        }
    }

    void change(int key, int w){
        std::size_t i = elements[key];
        heap[i].second = w;

        while (i > 1){
            std::size_t parent = i / 2;
            if (heap[i].second < heap[parent].second)
                swap(i, parent);
            else
                break;
            
            i = parent;
        }
    }

};

class Graph{
private:
    std::vector<std::vector<std::pair<int, int>>> vertices;
public:

    std::size_t size;

    Graph(std::size_t n){
        size = n;
        vertices.resize(n);
    }

    void addEdge(int u, int v, int w){
        vertices[u].push_back({v, w});
    }

    friend int dijkstra(const Graph&, int, int);

};

int dijkstra(const Graph& gph, int s, int f) {
    std::size_t n = gph.size;

    PQueue pq;
    std::vector<int> dist(n, INF);

    s--; f--; 

    pq.insert(s, 0);
    dist[s] = 0;

    while (!pq.empty()) {
        auto curr = pq.pop_min();
        std::cout << "Current: " << curr.first+1 << " with weight " << curr.second << std::endl;
        int u = curr.first;

        // if (curr.second > dist[u]) continue;

        for (const auto& edge : gph.vertices[u]) {
            int v = edge.first;
            int w = edge.second;

            std::cout << '\t' << v+1 << ' ' << w << '\n';

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.insert(v, dist[v]); 
            }
        }
    }

    int res = dist[f];
    return res == INF ? -1 : res;
}


int main(int argc, char *argv[]){
    int n, s, f;
    std::cin >> n >> s >> f;

    Graph gph(n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int w;
            std::cin >> w;

            if (w != -1) {
                gph.addEdge(i, j, w);
            }
        }
    }

    std::cout << dijkstra(gph, s, f) << std::endl;

    return 0;
}
