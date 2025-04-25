#include <iostream>
#include <vector>
#include <algorithm>
// #include <cstddef>

struct node {
    int left_value;
    int right_value;
    std::size_t prefix;
    std::size_t suffix;
    std::size_t max_length;
    std::size_t len;
};

class segment_tree {
    private:
        std::size_t size;
        std::vector<node> arr;

        node merge(const node& a, const node& b) {
            if (a.max_length == 0) return b;
            if (b.max_length == 0) return a;
            node res;
            res.left_value = a.left_value;
            res.right_value = b.right_value;
            res.len = a.len + b.len;
            res.prefix = a.prefix;
            res.suffix = b.suffix;
            res.max_length      = std::max(a.max_length, b.max_length);
            if (a.right_value <= b.left_value) {
                res.max_length = std::max(res.max_length, a.suffix + b.prefix);
                if (a.prefix == a.len)       res.prefix = a.len + b.prefix;
                if (b.suffix == b.len)       res.suffix = b.len + a.suffix;
            }
            return res;
        }
public:
    explicit segment_tree(std::vector<int>& nums) {
        std::size_t n = nums.size();
        size = 1;
        while (size < n) size <<= 1;
        arr.assign(2 * size, node{0, 0, 0, 0, 0, 0});
        for (std::size_t i = 0; i < n; i++) {
            arr[size + i] = node{nums[i], nums[i], 1, 1, 1, 1};
        }
        for (std::size_t i = size - 1; i > 0; i--) {
            arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
        }
    }
    void change(std::size_t pos, int value) {
        pos--;
        pos += size;
        arr[pos] = node{value, value, 1, 1, 1, 1};
        while (pos > 1) {
            pos /= 2;
            arr[pos] = merge(arr[2 * pos], arr[2 * pos + 1]);
        }
    }
    std::size_t find(std::size_t l, std::size_t r) {
        l--; r--;
        l += size;
        r += size;
        node left = {0, 0, 0, 0, 0, 0}, right = {0, 0, 0, 0, 0, 0};
        while (l <= r) {
            if (l & 1)  left  = merge(left, arr[l++]);
            if (!(r & 1)) right = merge(arr[r--], right);
            l >>= 1;
            r >>= 1;
        }
        return merge(left, right).max_length;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::size_t n;
    std::cin >> n;
    std::vector<int> sweetness(n);
    for (std::size_t i = 0; i < n; i++) std::cin >> sweetness[i];
    segment_tree st(sweetness);
    std::size_t m;
    std::cin >> m;
    for (std::size_t i = 0; i < m; i++) {
        int type;
        std::size_t l;
        int r;
        std::cin >> type >> l >> r;
        if (type == 1)
            std::cout << st.find(l, static_cast<std::size_t>(r)) << "\n";
        else if (type == 2)
            st.change(l, r);
    }
    return 0;
}

