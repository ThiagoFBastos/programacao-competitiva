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

const int N = 1e3;

int cost[N][N];

void solve() {
	int n, m;

	cin >> n >> m;

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		cost[i][j] = -1;

	vector<vector<ii>> g(n);

	while(m--) {
		int i, j;
		char ch;
		cin >> i >> j >> ch;
		--i, --j;
		g[i].emplace_back(j, ch - 'a');
		g[j].emplace_back(i, ch - 'a');
	}

	for(auto& v : g) sort(v.begin(), v.end());

	priority_queue<tuple<int, int, int>> pq;
	int ans = INT_MAX;

	pq.emplace(0, 0, n - 1);

	while(!pq.empty()) {
		auto [c, i, j] = pq.top();

		pq.pop();

		c *= -1;

		if(cost[i][j] != -1) continue;

		cost[i][j] = c;

		if(i != j) {
			for(auto [u, _] : g[i]) {
				for(auto [v, __] : g[j]) {
					if(_ != __ || cost[u][v] != -1) continue;
					pq.emplace(-c - 2, u, v);
				}
			}
		}

		if(i == j) ans = min(ans, c);
		
		auto k = lower_bound(g[i].begin(), g[i].end(), make_pair(j, -1));

		if(k == g[i].end() || k->first != j) continue;
		
		ans = min(ans, c + 1);
	}

	if(ans == INT_MAX) {
		cout << "-1\n";
		return;
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

