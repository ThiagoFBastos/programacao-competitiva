#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m, k;
 
	cin >> n >> m >> k;
 
	vector<vector<int>> adj(n);
	vector<pair<int, int>> dist[2];
	queue<pair<int, int>> q;
 
	for(int i = 0; i < 2; ++i) dist[i].assign(n, make_pair(-1, -1));
 
	for(int i = 0; i < k; ++i) {
		int v;
		cin >> v;
		--v;
		q.emplace(v, 0);
		dist[0][v] = {0, v};
	}
 
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
 
	while(!q.empty()) {
		auto [v, k] = q.front();
		q.pop();
		
		for(int u : adj[v]) {
			auto [da1, a1] = dist[0][u];
			auto [da2, a2] = dist[1][u]; 
			auto [db, b] = dist[k][v];
 
			if(k == 0) {
				if(da1 == -1) {
					q.emplace(u, 0);
					dist[0][u] = {db + 1, b};
				} else if(da2 == -1 && a1 != b) {
					q.emplace(u, 1);
					dist[1][u] = {db + 1, b};
				}
			} else {
				if(da2 == -1 && b != a1) {
					q.emplace(u, 1);
					dist[1][u] = {db + 1, b};
				}
			}
		}
	}
 
	for(int i = 0; i < n; ++i) {
		auto [da1, a1] = dist[0][i];
		auto [da2, a2] = dist[1][i];
 
		if(a1 == i) cout << da2 << ' ';
		else cout << da1 << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
