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

using T = tuple<int, int, int, int>;

const int N = 1e5;

int sp[18][N];

void solve() {
	
	int n, m, q;

	cin >> n >> m >> q;

	vector<vector<T>> g(n);	
	vector<T> bus(m);

	for(int i = 0; i < m; ++i) {
		int a, b, s, t;
		cin >> a >> b >> s >> t;
		--a, --b;
		g[a].emplace_back(s, t, b, i);
		bus[i] = {a, b, s, t};
		sp[0][i] = i;
	}

	for(auto& v : g) sort(v.begin(), v.end());

	for(int i = 0; i < n; ++i) {
		for(auto [start, finish, city, id] : g[i]) {
			auto& v = g[city];
			auto k = lower_bound(v.begin(), v.end(), make_tuple(finish, -1, -1, -1));
			if(k == v.end()) continue;
			sp[0][id] = get<3>(*k);
		}
	}

	int lg = 32 - __builtin_clz(m);

	for(int i = 1; i < lg; ++i)
	for(int j = 0; j < m; ++j)
		sp[i][j] = sp[i - 1][sp[i - 1][j]];

	while(q--) {
		int x, y, z;

		cin >> x >> y >> z;

		--y;

		auto& v = g[y];

		auto k = lower_bound(v.begin(), v.end(), make_tuple(x, -1, -1, -1));

		if(k == v.end()) {
			cout << y + 1 << '\n';
			continue;
		}

		int b = get<3>(*k);

		for(int i = lg - 1; i >= 0; --i) {
			int u = sp[i][b];
			auto [city0, city1, start, finish] = bus[u];
			if(finish < z || z > start && z <= finish) b = u;
		}
	
		auto [city0, city1, start, finish] = bus[b];

		if(z <= start) cout << 1 + city0 << '\n';
		else if(z > finish) cout << 1 + city1 << '\n';
		else cout << 1 + city0 << ' ' << 1 + city1 << '\n';
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
