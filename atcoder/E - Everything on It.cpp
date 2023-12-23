#pragma GCC optimize("O3")
#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

auto exp(long long n, int p, int mod) {
	auto v = 1LL;
	for(; p > 0; p >>= 1) {
		if(p & 1) v = v * n % mod;
		n = n * n % mod;
	}
	return v;
}

const int N = 3e3 + 10;
long long fat[N], inv[N], invFat[N], g[N], f[N];

auto C(int n, int k, int mod) {
	return fat[n] * invFat[k] % mod * invFat[n - k] % mod;
}

int mod_sum(int x, int y) {
	if(x < 0) return x + y;
	else if(x >= y) return x - y;
	return x;
}

void solve() {
	int n, mod;
	cin >> n >> mod;
	
	vector<long long> p(n * n + 1);
	p[0] = 1;
	for(int i = 1; i <= n * n; ++i) p[i] = mod_sum(p[i - 1] << 1, mod);
	
	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invFat[i] = 1;
	for(int i = 2; i <= n; ++i) {
		fat[i] = fat[i - 1] * i % mod;
		inv[i] = inv[mod % i] * -(mod / i) % mod;
		invFat[i] = invFat[i - 1] * inv[i] % mod;
	}
	
	int cnt = exp(2, exp(2, n, mod - 1), mod);
	
	g[0] = 1;
	
	for(int i = 1; i <= n; ++i) {
		for(int j = i - 1; j >= 0; --j) {
			g[j + 1] = mod_sum(g[j + 1] + g[j], mod);
			g[j] = g[j] * (j + 1) % mod;
		}
		for(int j = 0; j <= i; ++j) f[i] = (f[i] + g[j] * p[(n - i) * j]) % mod;
		cnt = (cnt + (i & 1 ? -1 : 1) * C(n, i, mod) * f[i] % mod * exp(2, exp(2, n - i, mod - 1), mod)) % mod;
	}
	
	cout << (cnt + mod) % mod << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

