#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

const int N = 2e3 + 10;

int dp[N][N], sz[N], depth[N], tmp[N], n, k;
vector<int> adj[N];

void merge(int u, int v) {
	for(int i = 0; i <= sz[u] + sz[v]; ++i) tmp[i] = INF;
	for(int i = 0; i <= sz[u]; ++i) {
		for(int j = 0; j <= sz[v] && i + j + 1 <= k; ++j)
			tmp[max(i, j + 1)] = min(tmp[max(i, j + 1)], dp[u][i] + dp[v][j]);
		if(i <= k) tmp[i] = min(tmp[i], dp[u][i] + sz[v]);
	}
	sz[u] += sz[v];
	memcpy(dp[u], tmp, sizeof(int) * (1 + sz[u]));
}

void dfs(int u, int p) {
	sz[u] = 1;
	for(int i = 0; i <= n; ++i) dp[u][i] = INF;
	dp[u][0] = 0;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		merge(u, v);
	}
}

void solve() {
	cin >> n >> k;
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b); adj[b].pb(a);
	}
	dfs(0, -1);
	int ans = INF;	
	for(int u = 0; u < n; ++u)
		for(int i = 0; i <= k; ++i)
			ans = min(ans, dp[u][i] + n - sz[u]);
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
