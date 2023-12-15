#include "bits/stdc++.h"
using namespace std;
int n, m, tms;
vector<vector<int>> g;
vector<int> lo, t;
vector<pair<int, int>> b;
void dfs(int u, int p = -1) {
	lo[u] = t[u] = tms++;
	for(int v : g[u]) {
		if(t[v] == -1) {
			dfs(v, u);
			if(lo[v] > t[u]) b.push_back({u + 1, v + 1});
			lo[u] = min(lo[u], lo[v]);
		} else if(v != p) lo[u] = min(lo[u], t[v]);
	}
}
void solve() {
	cin >> n >> m;
	g.resize(n);
	t.assign(n, -1);
	lo.resize(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(0);
	cout << size(b) << '\n';
	for(auto [u, v] : b) cout << u << ' ' << v << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
