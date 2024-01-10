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

const i64 INF = 1e15L;

void solve() {
	int n, m;

	cin >> n >> m;

	vector<vector<int>> g(n);
	vector<int> h(n);
	vector<i64> cost(n, -INF);
	priority_queue<pair<i64, int>> pq;

	for(int& v : h) cin >> v;

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	pq.push(make_pair(0LL, 0));

	while(!pq.empty()) {
		auto [c, v] = pq.top();
		pq.pop();
		if(cost[v] >= c) continue;
		cost[v] = c;
		for(int u : g[v]) {
			i64 X;
			if(h[u] <= h[v]) X = h[v] - h[u] + c;
			else X = c - 2 * (h[u] - h[v]);
			if(cost[u] >= X) continue;
			pq.emplace(X, u);
		}
	}

	cout << *max_element(cost.begin(), cost.end()) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
