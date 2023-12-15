#include "bits/stdc++.h"
using namespace std;
int n, m, tms;
vector<vector<int>> g;
vector<int> lo, t, j;
void dfs(int u, int p = -1) {
	bool flag = false;
	int cnt = 0;
	lo[u] = t[u] = tms++;
	for(int v : g[u]) {
		if(t[v] == -1) {
			dfs(v, u);
			++cnt;
			if(p != -1 && lo[v] >= t[u]) flag = true;
			lo[u] = min(lo[u], lo[v]);
		} else if(v != p) lo[u] = min(lo[u], t[v]);
	}
	if(p == -1 && cnt > 1) flag = true;
	if(flag) j.push_back(u + 1);
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
	for(int v = 0; v < n; ++v) {
		if(t[v] != -1) continue;
		dfs(v);
	}
	cout << size(j) << '\n';
	for(int v : j) cout << v << ' ';
	cout << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
