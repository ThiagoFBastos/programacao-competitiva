#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n, m, cnt = 0;
	
	cin >> n >> m;
	
	vector<vector<int>> g(n);
	vector<bool> vis(n, false);
	
	while(m--) {
		int x, y, z;
		cin >> x >> y >> z;
		--x, --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	
	for(int v = 0; v < n; ++v) {
		if(vis[v]) continue;
		++cnt;
		queue<int> q;
		vis[v] = true;
		q.push(v);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v : g[u]) {
				if(vis[v]) continue;
				vis[v] = true;
				q.push(v);
			}
		}
	}
	
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
