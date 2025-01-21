#include <iostream>
#include <stdexcept>
#include <string>
#include <random>

class BlackBoxException: public std::exception{
private:
    std::string message;
public:
    explicit BlackBoxException(const std::string& message): message(message){}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class BlackBoxNullSetException: public BlackBoxException{
public:
    explicit BlackBoxNullSetException(const std::string& message): BlackBoxException(message){}
};

class BlackBoxOverflowException: public BlackBoxException{
public:
    explicit BlackBoxOverflowException(const std::string& message): BlackBoxException(message){}
};

template <typename T>
class BlackBox{
private:
    T *data = nullptr;
    size_t size = 0;
    std::random_device rd;
    mutable std::mt19937 gen{rd()};

    [[nodiscard]] size_t random_element_fetcher() const {
        if (size == 0) {
            throw BlackBoxNullSetException("BlackBox has no elements in it.");
        }
        std::uniform_int_distribution<size_t> distrib(0, size - 1);
        return distrib(gen);
    }

    void element_popper(size_t index) {
        T* temp_data = new T[size - 1];
        size_t temp_index = 0;

        for (size_t i = 0; i < size; ++i) {
            if (i != index) {
                temp_data[temp_index++] = data[i];
            }
        }
        delete[] data;
        data = temp_data;
        size--;
    }

public:
    BlackBox() = default;

    BlackBox(T* array, size_t size) {
        if (size <= 100) {
            this->size = size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = array[i];
            }
        }
        else {
            delete[] data;
            throw BlackBoxOverflowException("BlackBox may only contain 100 elements.");
        }
    }

    ~BlackBox() {
        std::cout << "BlackBox destroyed" << std::endl;
        delete[] data;
    }

    void push(const T& element) {
        T* temp_data = new T[size + 1];
        for (size_t i = 0; i < size; i++){
            temp_data[i] = data[i];
        }
        temp_data[size] = element;
        delete[] data;
        data = temp_data;
        size++;
    }

    void pop() {
        try{
            size_t index_to_pop = random_element_fetcher();
            std::cout << data[index_to_pop] << '\n';
            element_popper(index_to_pop);
        }
        catch (BlackBoxNullSetException &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void xpop() const{
        try{
            size_t index_to_pop = random_element_fetcher();
            std::cout << data[index_to_pop] << '\n';
        }
        catch (BlackBoxNullSetException &e) {
            std::cerr << e.what() << std::endl;
        }
    }


};

int main(int argc, char** argv){
    int arr[100];
    int *other_arr;
    void *varr;

    BlackBox<int> bb(arr, 101);

    bb.xpop();
}