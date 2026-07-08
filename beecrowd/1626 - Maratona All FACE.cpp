#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7, N = 1e5 + 5;

long long fat[N], sum_divisors[N], max_factor[N], power[N];

long long binExp(long long n, long long p) {
    auto ans {1LL};

    n %= MOD;

    for(; p > 0; p >>= 1) {
        if(p & 1)
            ans = ans * n % MOD;

        n = n * n % MOD;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fat[0] = 1;
    for(int i = 1; i < N; ++i)
        fat[i] = i * fat[i - 1] % MOD;

    for(int p = 2; p < N; ++p) {
        if(max_factor[p])
            continue;

        for(int i = p; i < N; i += p)
            max_factor[i] = p;
    }

    sum_divisors[1] = 1;

    for(int i = 2; i < N; ++i) {
        sum_divisors[i] = sum_divisors[i - 1];

        for(int k = i; k > 1; ) {
            int raised {};
            int prime = max_factor[k];

            while(k % prime == 0) {
                raised++;
                k /= prime;
            }

            sum_divisors[i] = sum_divisors[i] * binExp((binExp(prime, power[prime] + 1) - 1) * binExp(prime - 1, MOD - 2), MOD - 2) % MOD;
            power[prime] += raised;
            sum_divisors[i] = sum_divisors[i] * (binExp(prime, power[prime] + 1) - 1)  % MOD * binExp(prime - 1, MOD - 2) % MOD;
        }
    }

    int n;

    while(cin >> n)
        cout << ((sum_divisors[n] - fat[n]) % MOD + MOD) % MOD << ' ' << fat[n] << '\n';

    return 0;
}