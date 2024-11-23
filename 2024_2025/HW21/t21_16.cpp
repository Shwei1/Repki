#include <iostream>
#include <algorithm>

template <typename input_iterator, typename output_iterator, typename predicate, typename transform>
output_iterator transform_if(input_iterator first, input_iterator last, output_iterator result, predicate pred, transform transform_){

    for (; first != last; ++first) {
        if (pred(*first)) {
            *result++ = transform_(*first);
        }
    }
    return result;
}

int main() {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> output;

    auto it = transform_if(input.begin(), input.end(), std::back_inserter(output),
                           [](int x) { return x % 2 == 0; },
                           [](int x) { return x * x; });


    for (int num : output) {
        std::cout << num << " ";
    }

}
