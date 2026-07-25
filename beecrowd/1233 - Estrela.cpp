#include <bits/stdc++.h>

using namespace std;

constexpr int N = 46345;

bitset<N> is_prime;
vector<int> primes;

void computePrimes() {
    is_prime.set();

    for(int p = 2; p * p < N; ++p) {
        if(!is_prime[p])
            continue;
        for(int i = p * p; i < N; i += p)
            is_prime[i] = 0;
    }

    auto rng = views::iota(2, N) | views::filter([&](int n) {
        return static_cast<bool>(is_prime[n]);
    });

    ranges::copy(rng, back_inserter(primes));
}

int phi(int n) {
    int answer = n;

    for(int p : primes) {
        if(1ll * p * p > n)
            break;
        else if(n % p)
            continue;

        while(n % p == 0) n /= p;

        answer -= answer / p;
    }

    if(n > 1) answer -= answer / n;

    return answer;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	computePrimes();

    for(int n; cin >> n; ) {
        int tot = phi(n);
        cout << (tot + 1) / 2  << '\n';
    }

	return 0;
}
 