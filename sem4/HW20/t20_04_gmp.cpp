#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <gmp.h>

class segment_tree_gcd {
private:
    size_t size;
    mpz_t* tree;

public:
    explicit segment_tree_gcd(const std::vector<std::string>& nums) {
        size_t n;
        n = nums.size();
        size_t k;
        k = static_cast<size_t>(std::ceil(std::log2(n)));
        size = 1;
        size <<= k;
        tree = new mpz_t[2 * size];
        for (size_t i = 0; i < 2 * size; ++i) {
            mpz_init(tree[i]);
        }
        for (size_t i = 0; i < n; ++i) {
            mpz_set_str(tree[size + i], nums[i].c_str(), 10);
        }
        for (size_t j = size - 1; j > 0; --j) {
            mpz_gcd(tree[j], tree[2 * j], tree[2 * j + 1]);
        }
    }

    ~segment_tree_gcd() {
        for (size_t i = 0; i < 2 * size; ++i) {
            mpz_clear(tree[i]);
        }
        delete[] tree;
    }

    void change(size_t l, const std::string& val) {
        size_t idx;
        idx = size + l - 1;
        mpz_set_str(tree[idx], val.c_str(), 10);
        while (idx > 1) {
            idx /= 2;
            mpz_gcd(tree[idx], tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void find(size_t l, size_t r, mpz_t result) const {
        mpz_set_ui(result, 0);
        mpz_t tmp;
        mpz_init(tmp);
        l += size - 1;
        r += size - 1;
        while (l <= r) {
            if (l & 1) {
                mpz_gcd(tmp, result, tree[l]);
                mpz_set(result, tmp);
                ++l;
            }
            if (!(r & 1)) {
                mpz_gcd(tmp, result, tree[r]);
                mpz_set(result, tmp);
                --r;
            }
            l >>= 1;
            r >>= 1;
        }
        mpz_clear(tmp);
    }
};

class segment_tree_lcm {
private:
    size_t size;
    mpz_t* tree;

public:
    explicit segment_tree_lcm(const std::vector<std::string>& nums) {
        size_t n;
        n = nums.size();
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        tree = new mpz_t[2 * size];
        for (size_t i = 0; i < 2 * size; ++i) {
            mpz_init(tree[i]);
            mpz_set_ui(tree[i], 1);
        }
        for (size_t i = 0; i < n; ++i) {
            mpz_set_str(tree[size + i], nums[i].c_str(), 10);
        }
        for (size_t j = size - 1; j > 0; --j) {
            mpz_lcm(tree[j], tree[2 * j], tree[2 * j + 1]);
        }
    }

    ~segment_tree_lcm() {
        for (size_t i = 0; i < 2 * size; ++i) {
            mpz_clear(tree[i]);
        }
        delete[] tree;
    }

    void change(size_t l, const std::string& val) {
        size_t idx;
        idx = size + l - 1;
        mpz_set_str(tree[idx], val.c_str(), 10);
        while (idx > 1) {
            idx /= 2;
            mpz_lcm(tree[idx], tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void find(size_t l, size_t r, mpz_t result) const {
        mpz_set_ui(result, 1);
        mpz_t tmp;
        mpz_init(tmp);
        l += size - 1;
        r += size - 1;
        while (l <= r) {
            if (l & 1) {
                mpz_lcm(tmp, result, tree[l]);
                mpz_set(result, tmp);
                ++l;
            }
            if (!(r & 1)) {
                mpz_lcm(tmp, result, tree[r]);
                mpz_set(result, tmp);
                --r;
            }
            l >>= 1;
            r >>= 1;
        }
        mpz_clear(tmp);
    }
};

int main() {

    size_t n;
    std::cin >> n;
    std::vector<std::string> init(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> init[i];
    }

    segment_tree_gcd st1(init);
    segment_tree_lcm st2(init);

    size_t m;
    std::cin >> m;
    for (size_t qi = 0; qi < m; ++qi) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 1) {
            size_t l;
            size_t r;
            std::cin >> l;
            std::cin >> r;
            mpz_t g;
            mpz_init(g);
            mpz_t L;
            mpz_init(L);
            st1.find(l, r, g);
            st2.find(l, r, L);
            int cmp;
            cmp = mpz_cmp(g, L);
            if (cmp < 0) {
                std::cout << "wins\n";
            } else if (cmp > 0) {
                std::cout << "loser\n";
            } else {
                std::cout << "draw\n";
            }
            mpz_clear(g);
            mpz_clear(L);
        } else {
            size_t pos;
            std::cin >> pos;
            std::string val;
            std::cin >> val;
            st1.change(pos, val);
            st2.change(pos, val);
        }
    }

    return 0;
}