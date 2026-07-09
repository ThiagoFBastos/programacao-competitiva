#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e6 + 5;

int max_factor[N], hiperprimes[N];
bitset<N> is_prime;

int divisors(int n) {
    int cnt {1};

    while(n != 1) {
        int prime = max_factor[n];
        int raised {};

        do
        {
            raised++;
            n /= prime;
        } while (n % prime == 0);
        
        cnt *= 1 + raised;
    }

    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    is_prime.set();
    
    for(int p = 2; p < N; ++p) {
        if(!is_prime[p])
            continue;

        max_factor[p] = p;

        for(int i = 2 * p; i < N; i += p) {
            is_prime[i] = 0;
            max_factor[i] = p;
        }
    }

    for(int i = 2; i < N; ++i) {
        int divs = divisors(i);
        int add = static_cast<int>(is_prime[divs]);
        hiperprimes[i] = hiperprimes[i - 1] + add;
    }

    int n;

    while(cin >> n)
        cout << hiperprimes[n] << '\n';

    return 0;
}