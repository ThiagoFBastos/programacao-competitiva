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

const int mod = 1e9 + 7, N = 2e5 + 100;
	
i64 sum[N];

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

i64 fat(int n) {
	i64 ans = 1;
	while(n > 0) {
		ans = ans * n % mod;
		--n;
	}
	return ans;
}

void solve() {
	int n, m, k, t;
	cin >> n >> m >> k;
	t = n * m;
	for(int i = 1; i <= max(n, m); ++i) sum[i] = (sum[i - 1] + i * (i + 1ll) / 2) % mod; 
	i64 dist = sum[n - 1] * m % mod * m % mod;
	dist = (dist + (2 * n + n * (n - 1ll)) % mod * sum[m - 1]) % mod;
	dist = (dist - n * sum[m - 1]) % mod;
	dist = (dist + mod) % mod;
	i64 cnt = fat(t - 2) * exp(fat(t - k) * fat(k - 2) % mod, mod - 2) % mod;
	cout << cnt * dist % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
