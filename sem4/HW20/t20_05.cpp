#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class segment_tree {
private:
    std::size_t size;
    std::vector<std::pair<int, int>> arr;

public:
    explicit segment_tree(std::vector<int>& nums) {
        std::size_t n = nums.size();
        size = 1;
        while (size < n) size <<= 1;
        arr.assign(2 * size, {1e9, -1e9});
        for (std::size_t i = 0; i < n; i++) {
            arr[size + i] = {nums[i], nums[i]};
        }
        for (std::size_t i = size - 1; i > 0; i--) {
            arr[i].first = std::min(arr[2 * i].first, arr[2 * i + 1].first);
            arr[i].second = std::max(arr[2 * i].second, arr[2 * i + 1].second);
        }
    }

    void change(std::size_t pos, int value) {
        pos += size - 1;
        arr[pos] = {value, value};
        while (pos > 1) {
            pos /= 2;
            arr[pos].first = std::min(arr[2 * pos].first, arr[2 * pos + 1].first);
            arr[pos].second = std::max(arr[2 * pos].second, arr[2 * pos + 1].second);
        }
    }

    int find(std::size_t l, std::size_t r) {
        l += size - 1;
        r += size - 1;
        int min_val = 1e9;
        int max_val = -1e9;
        while (l <= r) {
            if (l % 2 == 1) {
                min_val = std::min(min_val, arr[l].first);
                max_val = std::max(max_val, arr[l].second);
                l++;
            }
            if (r % 2 == 0) {
                min_val = std::min(min_val, arr[r].first);
                max_val = std::max(max_val, arr[r].second);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return max_val - min_val;
    }
};

auto main() -> int {
    std::size_t k;
    std::cin >> k;

    std::size_t n = 100000;
    std::vector<int> a(n);
    for (std::size_t i = 0; i < n; i++) {
        a[i] = (int)(((i + 1) * (i + 1)) % 12345 + ((i + 1) * (i + 1) * (i + 1)) % 23456);
    }

    segment_tree st(a);

    for (std::size_t i = 0; i < k; i++) {
        int x, y;
        std::cin >> x >> y;
        if (x > 0) {
            std::cout << st.find(x, y) << "\n";
        } else {
            st.change(-x, y);
        }
    }

    return 0;
}

