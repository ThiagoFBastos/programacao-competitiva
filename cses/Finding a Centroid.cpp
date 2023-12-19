#include "bits/stdc++.h"
using namespace std;
int n, w = -1;
vector<vector<int>> g;
vector<int> sz;
void dfs(int u, int p = -1) {
	sz[u] = 1;
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
void reroot(int u, int p = -1) {
	int max_sz = 0;
	for(int v : g[u]) max_sz = max(max_sz, sz[v]);
	if(max_sz <= n / 2) w = u;
	for(int v : g[u]) {
		if(v == p) continue;
		sz[u] -= sz[v];
		sz[v] += sz[u];
		reroot(v, u);
		sz[v] -= sz[u];
		sz[u] += sz[v];
	}
}
void solve() {
	cin >> n;
	g.resize(n);
	sz.resize(n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0);
	reroot(0);
	cout << 1 + w << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
