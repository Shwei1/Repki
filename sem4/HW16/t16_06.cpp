#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct directory {
    std::string name;
    std::vector<directory> subdirectories;

    explicit directory(std::string name_): name(std::move(name_)){}
};

std::vector<std::string> split(const std::string& line){
    std::vector<std::string> result;
    std::istringstream ss(line);
    std::string item;
    while (std::getline(ss, item, '\\')){
        result.push_back(item);
    }
    return result;
}

class disk {
public:
    directory root;

    disk(): root(directory("")) {}

    void write(const std::string& path){
        auto dirs = split(path);

        directory *curr = &root;

        for (auto const& dir: dirs){

            auto it = std::find_if(
                curr->subdirectories.begin(),
                curr->subdirectories.end(),
                [&](auto const& subdirectory) {return subdirectory.name == dir; }
            );

            if (it == curr->subdirectories.end()){

                curr->subdirectories.emplace_back(dir);
            
                std::sort(
                    curr->subdirectories.begin(),
                    curr->subdirectories.end(),
                    [](auto const& a, auto const& b){ return a.name < b.name; }
                );

                it = std::find_if(
                    curr->subdirectories.begin(),
                    curr->subdirectories.end(),
                    [&](auto const& subdirectory) {return subdirectory.name == dir; }
                );

            }

            curr = &*it;
        }

    }

    void output(const directory& d, int depth) const {
        if (!d.name.empty()) std::cout << std::string(depth-1, ' ') << d.name << std::endl;
        for (auto const& subd: d.subdirectories){
            output(subd, depth+1);
        }
    }

    void output() const {
        output(root, 0);
    }

};

int main(){
    std::size_t N;
    std::cin >> N;
    std::cin.get();
    
    disk C;

    for (std::size_t i = 0; i < N; i++){
        std::string line;
        std::getline(std::cin, line);

        C.write(line);
    }

    C.output();

    return 0;
}


