#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MOD = 1e9 + 7, N = 1e5 + 100;

vector<ii> adj[N];

int tcase, sub[N], depth[N], ans, n;

void dfs1(int u, int p) {
	sub[u] = 1;
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		dfs1(v, u);
		sub[u] += sub[v];
	}
}

void dfs2(int u, int p, i64 X) {
	X += sub[u];
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs2(v, u, X);
		i64 k = (X - (i64)depth[v] * sub[v]) % MOD;
		ans = (ans + k * sub[v] % MOD * w) % MOD;
	}
}

void solve() {
	cin >> n;
	ans = 0;
	for(int i = 0; i < n; ++i) adj[i].clear();
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}	
	dfs1(0, 0);
	dfs2(0, 0, 0);
	cout << "Case " << ++tcase << ": " << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
