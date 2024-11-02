#include <iostream>

class ThreeByteException: public std::exception {
private:
    std::string message;
public:
    explicit ThreeByteException(const std::string& message): message(message){}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class ThreeByteOverflowException: public ThreeByteException {
public:
    explicit ThreeByteOverflowException(const std::string& message): ThreeByteException(message){}
};

class ThreeByteDivisionByZeroException: public ThreeByteException {
public:
    explicit ThreeByteDivisionByZeroException(const std::string& message): ThreeByteException(message){}
};


class ThreeByte{
private:

    int32_t value;

    [[nodiscard]] bool check_overflow() const {

        int32_t masked_value = value & 0x7FFFFF;
        if (value < 0) {
            masked_value |= 0xFF800000;
        }
        return value == masked_value;
    }


public:

    ThreeByte(): value(0){}

    explicit ThreeByte(int32_t value){
        this->value = value;
        if(!check_overflow())
            throw ThreeByteOverflowException("Integer literal is too large to be represented in ThreeByte() type.");
    }

    ThreeByte operator+ (const ThreeByte& other) const {
        return ThreeByte(value + other.value);
    }

    ThreeByte operator- (const ThreeByte& other) const {
        return ThreeByte(value - other.value);
    }

    ThreeByte operator* (const ThreeByte& other) const {
        return ThreeByte(value * other.value);
    }

    bool operator== (const ThreeByte& other) const {
        return value == other.value;
    }

    bool operator!= (const ThreeByte& other) const {
        return value != other.value;
    }

    ThreeByte operator/ (const ThreeByte& other) const {
        if (other.value == 0){
            throw ThreeByteDivisionByZeroException("Division by zero is undefined.");
        }
        int32_t result = value / other.value;
        return ThreeByte(result);
    }

    ThreeByte& operator+=(const ThreeByte& other) {
        this->value += other.value;
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, ThreeByte& num) {
        int32_t temp;
        is >> temp;
        if (!ThreeByte(temp).check_overflow()) {
            throw ThreeByteOverflowException("Integer input is too large to be represented in ThreeByte() type.");
        }
        num.value = temp;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const ThreeByte& num) {
        os << num.value;
        return os;
    }

    [[nodiscard]] ThreeByte pow(unsigned n) const{
        int32_t result = value;
        for (int i = 1; i < n; ++i){
            result *= value;
        }
        return ThreeByte(result);
    }

    static ThreeByte sum(unsigned m, ThreeByte* three_byte_array) {
        ThreeByte result(0);
        for (int k = 0; k < m; k++){
            result += three_byte_array[k];
        }
        return result;
    }
};

int main(){
    ThreeByte tb(2);
    ThreeByte tb2(-5);
    const unsigned n = 6;

//    ThreeByte narr[n] = {
//            ThreeByte(342343243243),
//            ThreeByte(42343423),
//            ThreeByte(32423444),
//            ThreeByte(58345235)
//    };

    ThreeByte narr[n] = {
            ThreeByte(1),
            ThreeByte(2),
            ThreeByte(3),
            ThreeByte(-5),
            ThreeByte(8),
            ThreeByte(13)
    };

//    std::cout << ThreeByte::sum(n, narr) << std::endl;
//
//    std::cout << tb.pow(4) << std::endl;
//    std::cout << ThreeByte(1)/ThreeByte(0) << std::endl;

    try {
        std::cout << ThreeByte::sum(n, narr) << std::endl;
        std::cout << tb.pow(4) << std::endl;
        std::cin >> tb2; // 8388607, -8388608, -8388609
        std::cout << ThreeByte(1)/ThreeByte(0) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
