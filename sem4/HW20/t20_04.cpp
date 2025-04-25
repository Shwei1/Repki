#include <iostream>
#include <vector>
#include <cmath>

std::int64_t gcd(std::int64_t a, std::int64_t b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

std::int64_t lcm(std::int64_t a, std::int64_t b) {
    if (a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}

class segment_tree {
private:
    std::size_t size;
    std::vector<int> arr;

public:
    explicit segment_tree(std::vector<int>& nums) {
        auto k = static_cast<std::size_t>(std::ceil(std::log2(nums.size())));
        size = 1 << k;
        std::vector<int> vec(2 * size);

        for (std::size_t i = 0; i < nums.size(); i++) {
            vec[size + i] = nums[i];
        }

        for (std::size_t j = size - 1; j > 0; j--) {
            vec[j] = gcd(vec[2 * j], vec[2 * j + 1]);
        }

        arr = vec;
    }

    void change(std::size_t l, int r) {
        std::size_t i = size + l - 1;
        arr[i] = r;
        while (i > 1) {
            i /= 2;
            arr[i] = gcd(arr[2 * i], arr[2 * i + 1]);
        }
    }

    int find(std::size_t l, std::size_t r) {
        l += size - 1;
        r += size - 1;
        int res = 0;
        while (l <= r) {
            if (l % 2 == 1) res = gcd(res, arr[l++]);
            if (r % 2 == 0) res = gcd(res, arr[r--]);
            l /= 2;
            r /= 2;
        }
        return res;
    }
};

class segment_tree_2 {
private:
    std::size_t size;
    std::vector<std::int64_t> arr;

public:
    explicit segment_tree_2(std::vector<int>& nums) {
        size = 1;
        while (size < nums.size()) size <<= 1;
        arr.assign(2 * size, 1);

        for (std::size_t i = 0; i < nums.size(); i++) {
            arr[size + i] = nums[i];
        }

        for (std::size_t i = size - 1; i > 0; i--) {
            arr[i] = lcm(arr[2 * i], arr[2 * i + 1]);
        }
    }

    void change(std::size_t pos, int value) {
        pos += size - 1;
        arr[pos] = value;
        while (pos > 1) {
            pos /= 2;
            arr[pos] = lcm(arr[2 * pos], arr[2 * pos + 1]);
        }
    }

    std::int64_t find(std::size_t l, std::size_t r) {
        l += size - 1;
        r += size - 1;
        std::int64_t res = 1;
        while (l <= r) {
            if (l % 2 == 1) res = lcm(res, arr[l++]);
            if (r % 2 == 0) res = lcm(res, arr[r--]);
            l /= 2;
            r /= 2;
        }
        return res;
    }
};

auto main(void) -> int {
    std::size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (std::size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int m;
    std::cin >> m;
    segment_tree st1(arr);
    segment_tree_2 st2(arr);

    for (std::size_t j = 0; j < m; j++) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 1) {
            std::size_t l, r;
            std::cin >> l >> r;
            int g = st1.find(l, r);
            std::int64_t lcm_value = st2.find(l, r);

            if (g < lcm_value) std::cout << "wins\n";
            else if (g > lcm_value) std::cout << "loser\n";
            else std::cout << "draw\n";
        } else {
            std::size_t pos;
            int value;
            std::cin >> pos >> value;
            st1.change(pos, value);
            st2.change(pos, value);
        }
    }

    return 0;
}
