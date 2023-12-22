#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int N = 5e3 + 10, MOD = 998244353;

int dp[2][N][N], tmp[2][N];

void solve() {
	int n;
	cin >> n;

	vector<vector<int>> adj(n);
	vector<int> sz(n);

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	auto merge = [&](int u, int v) {
		for(int k = 0; k < 2; ++k)
			for(int i = 0; i <= sz[u] + sz[v]; ++i) 
			tmp[k][i] = 0;

		for(int i = 0; i <= sz[u]; ++i) {
			for(int j = 0; j <= sz[v]; ++j) {
				tmp[0][i + j] = (tmp[0][i + j] + (0ll + dp[0][v][j] + dp[1][v][j]) * dp[0][u][i]) % MOD;
				
				tmp[1][i + j] = (tmp[1][i + j] + (i64)dp[0][v][j] * dp[1][u][i]) % MOD;

				if(i&&j) tmp[1][i + j - 1] = (tmp[1][i + j - 1] + (i64)dp[1][v][j] * dp[1][u][i]) % MOD;
			}
		}

		sz[u] += sz[v];	
	
		for(int i = 0; i < 2; ++i)
			memcpy(dp[i][u], tmp[i], sizeof(int) * (1 + sz[u]));
	};

	auto dfs = [&](auto& dfs, int u, int p)->void {
		sz[u] = 1;
		dp[0][u][0] = 1; 
		dp[1][u][1] = 1;
		for(int v : adj[u]) {
			if(v == p) continue;
			dfs(dfs, v, u);
			merge(u, v);
		}
	};

	dfs(dfs, 0, -1);

	for(int x = 1; x <= n; ++x) cout << (dp[0][0][x] + dp[1][0][x]) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
