#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int n, cnt;
vector<vector<int>> g;
vector<int> folhas, tronco;

void dfs(int u, int p = -1) {
	folhas[u] = size(g[u]);
	for(int v : g[u]) {
		dfs(v, u);
		tronco[u] += folhas[v] >= 2;
	}
	if(p != -1 && tronco[u] > 0 && folhas[u] - 1 >= 2) {
		++cnt;
		folhas[u] = 0;
		--folhas[p];
	}
}

void solve() {
	cin >> n;
	g.resize(n);
	folhas.assign(n, 0);
	tronco.assign(n, 0);
	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		g[p - 1].emplace_back(i);
	}
	
	dfs(0);
	
	cout << cnt << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}