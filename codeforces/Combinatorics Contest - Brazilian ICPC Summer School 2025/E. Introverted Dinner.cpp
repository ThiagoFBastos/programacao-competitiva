#include <iostream>

constexpr int N = 1e5 + 10;
constexpr int MOD = 1e9 + 7;

int64_t fat[N], inv[N], invf[N];

int64_t C(int n, int k) {
    return n < k ? 0 : fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}

void preCompute(int n) {
    for(int i = 0; i < 2; ++i)
        fat[i] = invf[i] = inv[i] = 1;

    for(int i = 2; i <= n; ++i) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invf[i] = inv[i] * invf[i - 1] % MOD;
        fat[i] = i * fat[i - 1] % MOD;
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, k;

    std::cin >> n >> k;

    /*
        C(n - k - 1, k - 1) * (k - 1)! * n
    */

   preCompute(n);

   if(k == 1) {
        std::cout << n << '\n';
        return 0;
   }

    int64_t ans = C(n - k - 1, k - 1) * fat[k - 1] % MOD * n % MOD;

    std::cout << ans << '\n';
    
    return 0;
}