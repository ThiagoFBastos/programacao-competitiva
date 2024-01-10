#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;


const int mod = 1e9 + 7, N = 5e5 + 1;

i64 fat[N], inv[N], invFat[N];

i64 C(int n, int k) {
	return fat[n] * invFat[n - k] % mod * invFat[k] % mod;
}

i64 P(int n, int k) {
	return fat[n] * invFat[n - k] % mod;
}

void solve() {
	int n, m;

	cin >> n >> m;


	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invFat[k] = 1;
	for(int k = 2; k <= m; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = -(mod / k) * inv[mod % k] % mod;
		invFat[k] = invFat[k - 1] * inv[k] % mod;
	}

	i64 ans = P(m, n) * P(m, n) % mod;

	for(int k = 1; k <= n; ++k) {
		int sig = k & 1 ? -1 : 1;
		i64 X = C(n, k) * P(m, k) % mod;
		i64 Y = P(m - k, n - k);
		ans = (ans + sig * X * Y % mod * Y) % mod;
	}

	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

