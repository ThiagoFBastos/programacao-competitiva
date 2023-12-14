#include "bits/stdc++.h"
using namespace std;
int n, m, t_in;
vector<vector<pair<int, int>>> g; 
vector<pair<int, int>> edges;
vector<int> lo, t;
bool dfs(int u, int p) {
	lo[u] = t[u] = t_in++;
	for(auto [v, e] : g[u]) {
		if(t[v] == -1) {
			if(!dfs(v, u) || lo[v] > t[u]) return false;
			lo[u] = min(lo[u], lo[v]);
			edges[e] = {u, v};
		} else if(v != p) {
			lo[u] = min(lo[u], t[v]);
			edges[e] = {v, u};
		}
	}
	return true;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	g.resize(n);
	t.assign(n, -1);
	lo.resize(n);
	edges.resize(m);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back({b, i});
		g[b].push_back({a, i});
	}
	if(!dfs(0, -1) || t_in != n) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	for(auto [u, v] : edges) cout << u + 1 << ' ' << v + 1 << '\n';
	return 0;
}
