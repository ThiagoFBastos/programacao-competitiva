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

void solve() {
	
	i64 n;
	int x, m;

	cin >> n >> x >> m;

	if(n <= m) {
		i64 s = 0;
		for(int i = 1; i <= n; ++i) {
			s += x;
			x = (i64)x * x % m;
		}
		cout << s << '\n';
		return;
	}

	vector<i64> cycle;
	vector<int> vis(m, -1);
	auto K = make_pair(2 * m, 2 * m);
	i64 s = 0;

	for(int i = 1, y = x; i <= 2 * m; ++i) {
		if(vis[y] != -1) K = min(K, make_pair(vis[y], y));
		vis[y] = i;
		y = (i64)y * y % m;
	}

	auto [k, y] = K;

	for(int i = 1; i < k; ++i) {
		s += x;
		x = (i64)x * x % m;
	}

	n -= k - 1;

	cycle.push_back(0);
	for(int i = 1; ; ++i) {
		cycle.push_back(x);
		x = (i64)x * x % m;
		if(x == y) break;
	}

	for(int i = 1; i < (int)cycle.size(); ++i) cycle[i] += cycle[i - 1];

	s += cycle[n % int(cycle.size() - 1)];
	s += n / int(cycle.size() - 1) * cycle.back();

	cout << s << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
