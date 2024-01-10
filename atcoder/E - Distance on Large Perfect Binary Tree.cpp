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

const int mod = 998244353;

void solve() {

	int n, d, ans = 0;

	cin >> n >> d;

	vector<i64> p(2 * n + 1);
	p[0] = 1;

	for(int i = 1; i <= 2 * n; ++i) p[i] = 2 * p[i - 1] % mod;
	
	for(int a = 0; a <= min(n, d); ++a) {
		int b = d - a;
		if(b > n) continue;
		if(a && b) ans = (ans + 2 * p[a + b - 2] * (p[n - max(a, b)] - 1)) % mod;
		else ans = (ans + p[a + b] * (p[n - max(a, b)] - 1)) % mod;
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
