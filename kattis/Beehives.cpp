#include "bits/stdc++.h"

using namespace std;

void solve() {
	int n, m, ciclo;
	cin >> n >> m;
	
	ciclo = n;
	
	vector<vector<int>> g(n);
	vector<int> dist(n), pai(n);
	
	ciclo = n + 1;
	
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	for(int v = 0; v < n; ++v) {
		fill(dist.begin(), dist.end(), -1);
		queue<int> q;
		q.push(v);
		dist[v] = 0;
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			for(int y : g[x]) {
				if(dist[y] == -1) {
					pai[y] = x;
					dist[y] = 1 + dist[x];
					q.push(y);
				} else if(pai[x] != y && 1 + dist[x] > dist[y]) ciclo = min(ciclo, dist[x] + dist[y] + 1);
			}
		}
	}
	
	if(ciclo == n + 1) cout << "impossible\n";
	else cout << ciclo << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}