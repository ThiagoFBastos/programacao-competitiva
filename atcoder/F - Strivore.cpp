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

const int N = 2e6 + 100, mod = 1e9 + 7;

i64 fat[N], inv[N], invf[N], p25[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % mod * invf[n - k] % mod;
}

void solve() {
	
	int k, n;
	i64 cnt = 0, p = 1;
	string s;
		
	cin >> k >> s;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	p25[0] = 1, p25[1] = 25;

	n = s.size();

	for(int i = 2; i <= k + n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
		p25[i] = 25 * p25[i - 1] % mod;
	}

	for(int i = 0; i <= k; ++i) {
		i64 ways = p * C(k - i + n - 1, n - 1) % mod * p25[k - i];
		cnt = (cnt + ways) % mod;
		p = 26 * p % mod;
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
