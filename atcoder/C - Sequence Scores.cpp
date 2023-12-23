#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MOD = 998244353;
const int N = 5e3 + 10;

i64 pt[N], pt2[N], inv_pt2[N];

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p; p >>= 1) {
		if(p & 1) ans = ans * n % MOD;
		n = n * n % MOD;
	}
	return ans;
}

void solve() {
	int n, m;
	i64 ans = 1;

	cin >> n >> m;

	pt[0] = 1;
	for(int i = 1; i <= n; ++i) pt[i] = pt[i - 1] * m % MOD;
	
	ans = n * pt[n] % MOD;

	for(int i = 1; i < m; ++i) {
		i64 x = exp(m - i, MOD - 2), s = 0;

		pt2[0] = inv_pt2[0] = 1;
		for(int j = 1; j <= n; ++j) {
			pt2[j] = (m - i) * pt2[j - 1] % MOD;
			inv_pt2[j] = inv_pt2[j - 1] * x % MOD;
		}
	
		for(int j = 0; j < n; ++j) {
			ans = (ans - s * pt2[j] % MOD * pt[n - j - 1]) % MOD;
			s = (s + inv_pt2[j + 1] * pt[j]) % MOD;
		}
	}

	if(n >= 2) ans = (ans - (n - 1) * pt[n - 2]) % MOD;

	cout << (ans+MOD) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
