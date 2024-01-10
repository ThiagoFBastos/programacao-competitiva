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

const int mod = 998244353, N = 4e5 + 100;

i64 fat[N], inv[N], invf[N], pot[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % mod * invf[n - k] % mod;
}

void solve() {
	
	int n, m, k;
	i64 cnt = 0;

	cin >> n >> m >> k;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= 2 * n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = inv[i] * invf[i - 1] % mod;
	}

	pot[0] = 1;
	for(int i = 1; i <= n; ++i) pot[i] = (m - 1) * pot[i - 1] % mod;

	for(int i = 1; i <= n; ++i) {	
		if(n - i <= k)
			cnt = (cnt + C(n - 1, n - i) * m % mod * pot[i - 1]) % mod;
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
