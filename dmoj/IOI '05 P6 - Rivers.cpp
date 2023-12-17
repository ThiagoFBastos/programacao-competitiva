#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e2 + 10;
const i64 INF = 1e16L;

vector<ii> adj[N];
i64 dp[N][N][N], pre_dist[N], cp[N][N], load;
int w[N], n, k;

void dfs(int u) {

	for(int i = 0; i <= k + 1; ++i)
		for(int j = 0; j <= n; ++j)
			dp[u][i][j] = INF;

	for(int i = 0; i <= n; ++i) dp[u][i == u][i] = -pre_dist[i] * w[u];
		
	load += pre_dist[u] * w[u];

	for(auto [v, d] : adj[u]) {
		pre_dist[v] = pre_dist[u] + d;
		
		dfs(v);

		for(int i = 0; i <= k + 1; ++i)
			for(int j = 0; j <= n; ++j)
				cp[i][j] = INF;

		for(int i = 0; i <= k; ++i)
			for(int l = 0; i + l <= k + (!u); ++l)
				for(int j = 0; j <= n; ++j)
					cp[i + l][j] = min(cp[i + l][j], dp[v][i][j] + dp[u][l][j]);

		for(int i = 0; i <= k + 1; ++i)
			for(int j = 0; j <= n; ++j)
				dp[u][i][j] = cp[i][j];
	}

	if(u) {
		for(int i = 0; i <= k; ++i) {
			for(int j = 0; j <= n; ++j) {
				if(u == j) continue;
				dp[u][i][j] = min(dp[u][i][j], dp[u][i][u]);
			}
		}
		for(int i = 0; i <= k; ++i) dp[u][i][u] = INF;
	}
}

void solve() {
	cin >> n >> k;

	for(int i = 1; i <= n; ++i) {
		int v, d;
		cin >> w[i] >> v >> d;
		adj[v].emplace_back(i, d);
	}

	dfs(0);
	
	cout << load + dp[0][k + 1][0] << '\n';
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
