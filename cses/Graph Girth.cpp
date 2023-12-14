#include "bits/stdc++.h"
using namespace std;
using ii = pair<int, int>;
void solve() {
	int n, m, ans = INT_MAX;
	cin >> n >> m;
	vector<vector<ii>> g(n);
	vector<bool> in_use(m, true);
	vector<int> dist(n);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
	for(int v = 0; v < n; ++v) {
		for(auto [u, e] : g[v]) {
			queue<int> q;
			in_use[e] = false;
			fill(dist.begin(), dist.end(), -1);
			dist[v] = 0;
			q.push(v);
			while(!q.empty()) {
				int x = q.front();
				q.pop();
				if(dist[x] > ans) break;
				else if(x == u) {
					ans = min(ans, dist[x]);
					break;
				}
				for(auto [y, e] : g[x]) {
					if(dist[y] != -1 || !in_use[e]) continue;
					dist[y] = 1 + dist[x];
					q.push(y);
				}
			}
			in_use[e] = true;
		}
	}
	cout << (ans == INT_MAX ? -1 : 1 + ans) << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
