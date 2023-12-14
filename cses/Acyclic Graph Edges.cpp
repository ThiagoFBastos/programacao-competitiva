#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int MAXN = 1e5;
vector<int> G[MAXN];
int lv[MAXN];
void dfs(int v, int h) {
	lv[v] = h;
	for(int u : G[v]) {
		if(lv[u] == -1) dfs(u, h + 1);
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int k = 0; k < n; ++k) lv[k] = -1;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int v = 0; v < n; ++v) {
		if(lv[v] == -1)
			dfs(v, 0);
		for(int u : G[v]) {
			if(lv[u] > lv[v])
				cout << v + 1 << ' ' << u + 1 << '\n';
		}
	}
	return 0;
}
