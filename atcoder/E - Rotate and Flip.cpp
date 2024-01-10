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
	int n, m, q;

	cin >> n;

	vector<int> x(n), y(n);
	int mul[2] = {1, 1};
	i64 sum[2] = {0, 0};

	for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
		
	cin >> m;

	vector<vector<ii>> Q(m + 1);	
	vector<ii> op(m);

	for(auto& [x, y] : op) {
		cin >> x;
		if(x > 2) cin >> y;
	}
	
	cin >> q;
	
	vector<pair<i64, i64>> query(q);
	
	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		Q[a].emplace_back(b - 1, i);
	}

	for(int i = 0; i <= m; ++i) {
		for(auto [k, id] : Q[i]) {
			i64 x0 = x[k] * mul[0] + sum[0];
			i64 y0 = y[k] * mul[1] + sum[1];
			query[id] = {x0, y0};
		}
		if(i == m) continue;
		auto [t, v] = op[i];
		if(t == 1) {
			mul[0] *= -1;
			sum[0] *= -1;
			swap(mul[0], mul[1]);
			swap(sum[0], sum[1]);
			swap(x, y);
		} else if(t == 2) {
			mul[1] *= -1;
			sum[1] *= -1;
			swap(mul[0], mul[1]);
			swap(sum[0], sum[1]);
			swap(x, y);
		} else if(t == 3) {
			mul[0] *= -1;
			sum[0] *= -1;
			sum[0] += 2 * v;
		} else {
			mul[1] *= -1;
			sum[1] *= -1;
			sum[1] += 2 * v;
		}
	}

	for(auto [x, y] : query) cout << x << ' ' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

