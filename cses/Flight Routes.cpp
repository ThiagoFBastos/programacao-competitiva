#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 1e5;
	vector<pair<int, int>> G[MAXN];
	int n, m, k, routes[MAXN];
	long long cost[MAXN][10];
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	cin >> n >> m >> k;
	for(int i = 0; i < n; ++i) {
		routes[i] = 0;
		for(int j = 0; j < k; ++j)
			cost[i][j] = -1;
	}
	for(int i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		G[u - 1].push_back({v - 1, w});
	}
	pq.push({0, 0});
	while(!pq.empty()){
		auto [c, v] = pq.top();
		pq.pop();
		if(routes[v] < k) {
			cost[v][routes[v]++] = c;
			if(v == n - 1 && routes[v] == k) break;
			for(auto [u, w] : G[v]) {
				if(routes[u] < k) pq.push({w + c, u});
			}
		}
	}
	for(int i = 0; i < routes[n - 1]; ++i) cout << cost[n - 1][i] << ' ';
	cout << '\n';
	return 0;
}
