#include "bits/stdc++.h"
using namespace std;

const int N = 2e6 + 10, mod = 1e9 + 7;

long long fat[N], inv[N], invfat[N];

auto C(int n, int k) {
	return fat[n] * invfat[k] % mod * invfat[n - k] % mod;
}

void solve() {
	int r1, c1, r2, c2, ans = 0;
	cin >> r1 >> c1 >> r2 >> c2;
	for(int r = r1; r <= r2; ++r) ans = (ans + C(r + c2 + 1, c2) - C(r + c1, c1 - 1)) % mod;
	cout << (ans + mod) % mod << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invfat[k] = 1;
	for(int k = 2; k < N; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = (-(mod / k) * inv[mod % k] % mod + mod) % mod;
		invfat[k] = inv[k] * invfat[k - 1] % mod;
	}
	solve();
	return 0;
}
