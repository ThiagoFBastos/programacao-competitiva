#include <iostream>

constexpr int MOD = 1e9 + 7;
constexpr int N = 1e5 + 10;

int64_t fat[N], inv[N], invf[N];

int64_t binExp(int64_t n, int k) {
    int64_t ans = 1;
    for(; k; k >>= 1) {
        if(k & 1)
            ans = ans * n % MOD;
        n = n * n % MOD;
    }
    return ans;
}

void preCompute(int n) {
    for(int i = 0; i < 2; ++i)
        fat[i] = inv[i] = invf[i] = 1;

    for(int i = 2; i <= n; ++i) {
        fat[i] = i * fat[i - 1] % MOD;
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invf[i] = inv[i] * invf[i - 1] % MOD;
    }
}

int64_t Comb(int n, int k) {
    return fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

/*
    n ^ k - \sum C(n, i) * (n - i)^k * (-1)^(i+1)
*/

    int n, k;

    std::cin >> k >> n;

    preCompute(n);

    int64_t ans = binExp(n, k);

    for(int i = 1; i < n; ++i) {
        int64_t zeroes = Comb(n, i) * binExp(n - i, k) % MOD;

        if(i % 2)
            ans -= zeroes;
        else
            ans += zeroes;
        ans %= MOD;
    }

    ans = (ans + MOD) % MOD;

    std::cout << ans << '\n';

    return 0;
}