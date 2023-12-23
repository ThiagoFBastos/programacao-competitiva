#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

int n, m;

vector<vector<ii>> g;
vector<int> label;

void dfs(int u) {
	for(auto [v, c] : g[u]) {
		if(label[v] != -1) continue;
		if(label[u] != c) label[v] = c;
		else label[v] = c == 1 ? 2 : 1;
		dfs(v);
	}
}

void solve() {
	cin >> n >> m;
	g.resize(n);
	label.assign(n, -1);
	for(int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		--u, --v;
		g[u].emplace_back(v, c);
		g[v].emplace_back(u, c);
	}
	label[0] = 1;
	dfs(0);
	for(int x : label) cout << x << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}

