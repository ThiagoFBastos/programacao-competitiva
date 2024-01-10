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

const int mod = 1e9 + 7;

void solve() {
	
	int n;
	
	map<pair<i64, i64>, int> S;
	i64 ans = 1, zero = 0;

	cin >> n;

	vector<i64> p(n + 1);
	p[0] = 1;
	for(int i = 1; i <= n; ++i) p[i] = 2 * p[i - 1] % mod;

	for(int i = 0; i < n; ++i) {
		i64 x, y;
		cin >> x >> y;
		if(x < 0 || !x && y < 0) x *= -1, y *= -1;
		i64 g = gcd(x, abs(y));
		if(abs(x) + abs(y) == 0) ++zero;
		else ++S[{x / g, y / g}];
	}

	while(!S.empty()) {
		auto [dx, dy] = S.begin()->first;

		i64 _dx = -dy, _dy = dx;

		if(_dx < 0) _dx *= -1, _dy *= -1;

		if(S.count(make_pair(_dx, _dy))) {
			ans = ans * (p[S.begin()->second] + p[S[{_dx, _dy}]] - 1) % mod;
			S.erase(make_pair(_dx, _dy));
		} else ans = ans * p[S.begin()->second] % mod;

		S.erase(S.begin());
	}

	ans = (ans + zero - 1) % mod;

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
