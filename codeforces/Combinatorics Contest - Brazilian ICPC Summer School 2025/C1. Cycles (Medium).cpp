#include <iostream>

constexpr int MOD = 1e9 + 7;
constexpr int N = 1e3 + 10;

int dp[N];
int64_t fat[N], inv[N], invf[N];

void preCompute(int n) {
    for(int i = 0; i < 2; ++i)
        fat[i] = inv[i] = invf[i] = 1;

    for(int i = 2; i <= n; ++i) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invf[i] = inv[i] * invf[i - 1] % MOD;
        fat[i] = fat[i - 1] * i % MOD;
    }
}

int64_t Comb(int n, int k) {
    return fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    dp[0] = 1;

    int T, n;
    int64_t ans {};

    std::cin >> n >> T;

    preCompute(n);

    for(int i = 1; i <= n; ++i) {
        for(int j = n; j >= 0; --j) {
            int64_t combs = 1;
            for(int k = 1; k * i + j <= n; ++k) {

                combs = combs * Comb(n - (k - 1) * i - j, i) % MOD * fat[i - 1] % MOD;

                int64_t count = dp[j] * combs % MOD * invf[k] % MOD;

                dp[k * i + j] = (dp[k * i + j] + count) % MOD;

                if(i >= T && k * i + j == n)
                    ans = (ans + count) % MOD;
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}