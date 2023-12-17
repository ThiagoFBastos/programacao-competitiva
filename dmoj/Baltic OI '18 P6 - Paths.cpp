#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, m, k;
	cin >> n >> m >> k;	
	vector<vector<int>> g(n);
	vector<int> c(n);
	vector<array<long long, 32>> paths(n), a(n);
	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		paths[i].fill(0);
		paths[i][1 << --c[i]] = 1;
	}
	while(m--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	auto ans = 0LL;
	for(int i = 1; i < k; ++i) {
		for(int v = 0; v < n; ++v) a[v].fill(0);
		for(int v = 0; v < n; ++v) {
			for(int u : g[v]) {
				for(int j = 0; j < (1 << k); ++j) {
					if(j & 1 << c[u]) continue;
					a[u][j | 1 << c[u]] += paths[v][j];
				}
			}
		}
		for(int v = 0; v < n; ++v) {
			paths[v].fill(0);
			for(int j = 0; j < (1 << k); ++j) {
				paths[v][j] += a[v][j];
				ans += a[v][j];
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
