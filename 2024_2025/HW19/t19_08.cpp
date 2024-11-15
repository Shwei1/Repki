#include <list>
#include <iostream>
#include <stdexcept>
#include <iomanip>

template <typename T>
struct NumberStorage {
    std::list<T> numbers;

    void add(T num){
        numbers.push_back(num);
    }

    void del(T num){
        if (numbers.empty()){
            throw std::out_of_range("NumberStorage is empty.");
        }
        auto it = std::find(numbers.begin(), numbers.end(), num);
        if (it != numbers.end()){
            numbers.erase(it);
        }
        else {
            throw std::runtime_error("Specified number is not in NumberStorage.");
        }
    }

    T find_closest(T num){
        T closest = numbers.front();
        for (T potential_closest: numbers){
            if (fabs(potential_closest - num) < fabs(closest - num) && potential_closest != num){
                closest = potential_closest;
            }
        }
        return closest;
    }

    const T& operator[](std::size_t index) const {
        if (index >= numbers.size()) {
            throw std::out_of_range("Index out of range");
        }
        auto it = numbers.begin();
        std::advance(it, index);
        return *it;
    }

    friend std::ostream& operator<<(std::ostream& os, const NumberStorage<T>& storage){
        for (T number: storage.numbers){
            os << number << ' ';
        }
        return os;
    }
};

int main(){
    NumberStorage<int> my_storage_ints;

    my_storage_ints.add(1);
    my_storage_ints.add(2);
    my_storage_ints.add(5);
    my_storage_ints.add(6);
    my_storage_ints.del(6);

    std::cout << my_storage_ints << std::endl;
    std::cout << my_storage_ints.find_closest(5) << std::endl;
    std::cout << my_storage_ints[0] << std::endl;

    std::cout << "Setting a NumberStorage with long double:" << std::endl;

    NumberStorage<long double> my_storage_llfs;

    my_storage_llfs.add(1.000000004);
    my_storage_llfs.add(1.000000003);
    my_storage_llfs.add(1.000000002);
    my_storage_llfs.add(2.484834342347328478234);

    std::cout << std::fixed << std::setprecision(10);

    my_storage_llfs.del(my_storage_llfs[3]);

    std::cout << "Output of long double storage: " << my_storage_llfs << std::endl;
    try {
        std::cout << "Trying to output something out of range: " << my_storage_llfs[3] << std::endl;
    }
    catch (const std::out_of_range& e){
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << my_storage_llfs.find_closest(1.000000004) << std::endl;
    std::cout << my_storage_llfs.find_closest(1.000000003) << std::endl;

    NumberStorage<float> monke;
    try {
        monke.del(13.0 / 37);
    }
    catch (const std::out_of_range& e){
        std::cout << e.what() << std::endl;
    }

}