#include "bits/stdc++.h"
using namespace std;
const int MAXN = 5e4;
bitset<MAXN> S[MAXN];
vector<bool> vis;
vector<int> topo;
vector<vector<int>> g;
int n, m;
void dfs(int u) {
	vis[u] = true;
	for(int v : g[u]) {
		if(vis[v]) continue;
		dfs(v);
	}
	topo.push_back(u);
}
void solve() {
	cin >> n >> m;
	g.resize(n);
	vis.assign(n, false);
	vector<vector<int>> G(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		G[b].push_back(a);
	}
	for(int v = 0; v < n; ++v) {
		S[v][v] = 1;
		if(!vis[v]) dfs(v);
	}
	for(int v : topo)
		for(int u : G[v])
			S[u] |= S[v];
	for(int v = 0; v < n; ++v) cout << S[v].count() << ' ';
	cout << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
