#include "bits/stdc++.h"
using namespace std;

long long e[50][50];

void solve() {
	int n, m;

	cin >> n;
	
	vector<vector<pair<int, int>>> g(n);
	
	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
	
	for(int v = 0; v < n; ++v) {
		queue<int> q;
		memset(e[v], -1, sizeof e[v]);
		e[v][v] = 0;
		q.push(v);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(auto [w, pos] : g[u]) {
				if(e[v][w] != -1) continue;
				e[v][w] = e[v][u] | 1LL << pos;
				q.push(w);
			}
		}
	}
	
	cin >> m;
	
	vector<pair<int, int>> paths(m);
	vector<long long> edges(1 << m);
	auto cnt = 0LL;
	
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		paths[i] = {u, v};
	}
	
	edges[0] = 0;
	
	for(int k = 1; k < (1 << m); ++k) {
		int i = __builtin_ctz(k);
		auto [u, v] = paths[i];
		edges[k] = edges[k ^ 1 << i] | e[u][v];
		int n_edges = __builtin_popcountll(edges[k]);
		cnt += (__builtin_popcount(k) & 1 ? 1 : -1) * (1LL << (n - 1 - n_edges));
	}
	
	cout << (1LL << (n - 1)) - cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
