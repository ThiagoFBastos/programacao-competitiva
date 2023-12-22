#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;

	cin >> n;

	vector<vector<int>> g(n);
	vector<i64> dist(n, 0);
	vector<int> sz(n, 0);

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	function<void(int, int)> preProcess = [&](int u, int p) {
		sz[u] = 1;
		for(int v : g[u]) {
			if(v == p) continue;
			preProcess(v, u);
			sz[u] += sz[v];
			dist[u] += dist[v] + sz[v];
		}
	};

	function<void(int, int)> dfs = [&](int u, int p) {
		for(int v : g[u]) {
			if(v == p) continue;
			dist[v] = dist[u] + n - 2 * sz[v];
			dfs(v, u);
		}
	};

	preProcess(0, 0);
	dfs(0, 0);

	for(i64 v : dist) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
