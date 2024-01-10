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

const i64 INF = 1e18L, MAX = 1e17L;
const int N = 2600;

vector<ii> adj[N];
vector<int> g[N];
array<i64, N> dp[3];
int n, m, p;

vector<bool> vis;
vector<int> topo;

void dfs(int u) {
	vis[u] = true;
	for(int v : g[u]) {
		if(vis[v]) continue;
		dfs(v);
	}
	topo.push_back(u);
}

void solve() {
	i64 ans = 0;

	cin >> n >> m >> p;

	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		adj[a].emplace_back(b, c - p);
		g[b].push_back(a);
	}

	dp[0].fill(-INF);
	dp[0][0] = 0;
		
	for(int k = 0; k < 2; ++k) {
		for(int i = 1; i <= n; ++i) {
			for(int i = 0; i < n; ++i) dp[1][i] = dp[0][i];
			for(int u = 0; u < n; ++u)
			for(auto [v, w] : adj[u]) dp[1][v] = max(dp[1][v], dp[0][u] + w);
			swap(dp[0], dp[1]);
			ans = max(ans, dp[0][n - 1]);
		}
		if(k == 0) for(int i = 0; i < n; ++i) dp[2][i] = dp[0][i];
	}

	vis.assign(n, false);
	dfs(n - 1);

	for(int v : topo) {
		if(dp[0][v] < -MAX) continue;
		if(dp[0][v] != dp[2][v]) {
			cout << "-1\n";
			return;
		}
	}

	cout << ans << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(t--) solve();
}
