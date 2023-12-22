#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MOD = 998244353;

i64 sum(i64 l, i64 r) {
	return (r - l + 1ll) * (r + l) / 2 % MOD;
}

i64 count(int a, int b, int c, int d, int n, int m) {
	int k = c;

	while((a + k) % 2) ++k;

	if(k > d) return 0;
	
	i64 _n = (b - a + 2ll) / 2;
	i64 _m = (d - k + 2) / 2;
	i64 cnt = _n * _m % MOD, ans = 0;

	i64 p = (b - a) / 2;
	i64 q = (d - k) / 2;

	ans = (ans + cnt * k) % MOD;
	ans = (ans + m * (a - 1ll) % MOD * cnt) % MOD;
	ans = (ans + 2 * sum(0, p) * _m % MOD * m) % MOD;
	ans = (ans + 2 * sum(0, q) * _n) % MOD;

	return ans;
}

void solve() {
	int n, m, q;

	cin >> n >> m >> q;

	while(q--) {
		int a, b, c, d;

		cin >> a >> b >> c >> d;

		i64 ans = count(a, b, c, d, n, m);

		if(++a <= b) ans = (ans + count(a, b, c, d, n, m)) % MOD;
		
		cout << (ans + MOD) % MOD << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
