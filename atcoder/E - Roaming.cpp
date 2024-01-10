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

const int mod = 1e9 + 7, N = 4e5 + 100;

i64 fat[N], inv[N], invf[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % mod * invf[n - k] % mod;
}

void solve() {

	int n, k;
	i64 ans = 0;

	cin >> n >> k;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= 2 * n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}

	ans = C(2 * n - 1, n);

	if(k < n) {
		for(int i = k + 1; i < n; ++i) {
			int j = n - i;
			int k = 2 * n - i - j - 1;
			if(k < j) continue;
			ans = (ans - C(n, i) * C(k, n - j)) % mod;
		}
		ans = (ans + mod) % mod;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
