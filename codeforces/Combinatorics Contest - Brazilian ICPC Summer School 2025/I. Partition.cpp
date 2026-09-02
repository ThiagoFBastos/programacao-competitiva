#include <iostream>

constexpr int MOD = 1e9 + 7;

int64_t bin_exp(int64_t n, int k) {
    int64_t ans {1};

    for(; k; k >>= 1) {
        if(k & 1)
            ans = ans * n % MOD;
        n = n * n % MOD;
    }

    return ans;
}

int64_t f(int n) {
    return bin_exp(2, n - 1);
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;

    std::cin >> n;

    std::cout<<f(n)<<'\n';

    return 0;
}