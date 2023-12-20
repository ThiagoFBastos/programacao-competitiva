#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
vector<int> G[MAXN];
unordered_set<int> E[MAXN];
int tour[1 + 2 * MAXN], k = 0, n, m;
void dfs_1(int v) {
	while(!G[v].empty()) {
		int u = G[v].front();
		G[v].erase(G[v].begin());
		if(!E[u].count(v)) {
			E[v].insert(u);
			dfs_1(u);
		}
	}
	tour[k++] = v;
}
int vis = 0;
bool seen[MAXN];
void dfs_2(int v) {
	seen[v] = true;
	vis += G[v].size();
	for(int u : G[v])
		if(!seen[u]) dfs_2(u);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bool flag = true;
	for(int v = 0; v < n; ++v) {
		seen[v] = false;
		if(G[v].size() & 1) {
			flag = false;
			break;
		}
	}
	if(G[0].empty())
		flag = false;
	dfs_2(0);
	if(flag && vis == 2 * m) {
		dfs_1(0); 
		for(int v = 0; v <= m; ++v) 
			cout << tour[v] + 1 << ' ';
		cout << '\n';
	}
	else
		cout << "IMPOSSIBLE\n";
	return 0; 	
}
