#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 31623, MOD = 1e9 + 7;
 
vector<int> primes;
bitset<N> is_prime;
 
void computePrimes() {
	is_prime.set();
 
	for(int p = 2; p * p < N; ++p) {
		if(!is_prime[p])
			continue;
 
		for(int i = 2 * p; i < N; i += p)
			is_prime[i] = 0;
	}
 
	for(int i = 2; i < N; ++i) {
		if(is_prime[i])
			primes.push_back(i);
	}
}
 
vector<int> factorize(int n) {
	vector<int> powk;
 
	for(int p : primes) {
		if(p * p > n) 
			break;
		else if(n % p)
			continue;
 
		int i {};
 
		while(n % p == 0) {n /= p; ++i;}
 
		powk.push_back(i);
	}
 
	if(n != 1)
		powk.push_back(1);
 
	return powk;
}
 
int count_arrays(int k, int n) {
 
	auto matrix_mul = [](int a[][2], int b[][2]) {
		int c[2][2] = {{0}};
 
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 2; ++k)
					c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
 
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				a[i][j] = c[i][j];
	};
 
	auto matrix_pow = [&matrix_mul](int dest[][2], int a[][2], int p) {
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				dest[i][j] = i == j;
 
		for(; p; p >>= 1) {
			if(p & 1) matrix_mul(dest, a);
			matrix_mul(a, a);
		}
	};
 
	int t[2][2], a[2][2] = {{0, k}, {1, 1}};
 
	matrix_pow(t, a, n - 1);
 
	int ans {};
 
	for(int i = 0; i < 2; ++i)
		ans = (ans + 1ll * t[i][0] * k + t[i][1]) % MOD;
 
	return ans;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	computePrimes();
 
	int t;
 
	cin >> t;
 
	while(t--) {
		int n, k, ans {1};
 
		cin >> n >> k;
 
		auto powers = factorize(k);
 
		for(int a : powers)
			ans = 1ll * ans * count_arrays(a, n) % MOD;
		
		cout << ans << '\n';
	}
 
	return 0;
}
