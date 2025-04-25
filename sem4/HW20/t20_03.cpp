int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

class segment_tree{

    private:
        std::size_t size;
        std::vector<int> arr;

    public:
        explicit segment_tree(std::vector<int>&& nums){
            auto k = static_cast<std::size_t>(std::ceil(std::log2(nums.size())));
            size = 1 << k;

            std::vector<int> vec(2 * size);

            for (std::size_t i = 0; i < nums.size(); i++) {
                vec[size + i] = nums[i];
            }

            for (std::size_t j = size - 1; j > 0; j--) {
                vec[j] = gcd(vec[2 * j], vec[2 * j + 1]);
            }

            this->arr = vec;
        }

        void change(std::size_t l, int r){
            std::size_t i = size + l - 1;
            arr[i] = r;
            while (i > 1) {
                i /= 2;
                arr[i] = gcd(arr[2*i], arr[2*i + 1]);
            }          
        }

        int find(std::size_t l, std::size_t r) {
        l += size - 1; 
        r += size - 1;
        int res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res = gcd(res, arr[l]);
                l++;
            }
            if (r % 2 == 0) {
                res = gcd(res, arr[r]);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }

};


auto main(void) -> int{
    std::size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (std::size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int m;
    std::cin >> m;
    segment_tree st(std::move(arr));

    for (std::size_t j = 0; j < m; j++) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 1) {  
            std::size_t p1, p2;
            std::cin >> p1 >> p2;
            std::cout << st.find(p1, p2) << std::endl;
        }
        else {
            std::size_t p1;
            int p2;
            std::cin >> p1 >> p2;
            st.change(p1, p2);
        }
    }

    return 0;
}
