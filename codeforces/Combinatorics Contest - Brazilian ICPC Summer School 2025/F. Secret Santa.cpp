#include <iostream>
#include <string>

constexpr int MOD = 1e9 + 7;
constexpr int N = 1e5 + 10;

int64_t inv[N], invf[N];

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    int64_t ans {};

    std::cin >> n;

    for(int i = 0; i < 2; ++i)
        inv[i] = invf[i] = 1;

    for(int i = 2; i <= n; ++i) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invf[i] = inv[i] * invf[i - 1] % MOD;
    }

    for(int i = 1; i <= n; ++i) {
        if(i % 2 == 0)
            ans -= invf[i];
        else
            ans += invf[i];
        ans %= MOD;
    }

    std::cout<<(ans+MOD)%MOD<<'\n';

    return 0;
}