#include <bits/stdc++.h>

using namespace std;

auto factors(int n) {
    vector<int> primes;

    for(int p = 2; p * p <= n; ++p) {
        if(n % p) continue;
        primes.push_back(p);
        while(n % p == 0) n /= p;
    }

    if(n > 1)
        primes.push_back(n);

    return primes;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    int a, b;

    cin >> a >> b;

    int c = gcd(a, b);
    long long L2 = 1;

    auto primes = factors(c);

    for(int p : primes) {
        int i = 0;

        while(c % p == 0) {
            c /= p;
            i ^= 1;
            L2 *= p;
        }

        if(i == 1) L2 *= p;
    }

    auto L = static_cast<long long>(sqrt(L2 + 0.0L));

    cout << L << '\n';

	return 0;
}
 