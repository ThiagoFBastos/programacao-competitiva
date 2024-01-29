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

const int N = 1e5 + 100;
const i64 INF = 1e16L;

vector<int> adj[N];
int a[N], t[N], n;
i64 dp[N][3];

void dfs(int u, int p) {
	dp[u][0] = a[u];
	dp[u][1] = 0;
	dp[u][2] = a[u];

	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		dp[u][0] += dp[v][0] - a[v];
		dp[u][1] += dp[v][0] - a[v];
		dp[u][2] += dp[v][0] - a[v];
	}

	i64 X = -INF, Y = -INF, Z = dp[u][0];

	for(int v : adj[u]) {
		if(v == p) continue;
		Y = max(Y, Z + a[v]);
		if(t[v] == 3) dp[u][0] = max(dp[u][0], Z + X - (dp[v][0] - a[v]) + max(dp[v][0], dp[v][2]));
		X = max(X, -(dp[v][0] - a[v]) + dp[v][2]);
	}

	X = -INF;

	reverse(adj[u].begin(), adj[u].end());

	for(int v : adj[u]) {
		if(v == p) continue;
		dp[u][0] = max(dp[u][0], Z + a[v]);		
		if(t[v] == 3) dp[u][0] = max(dp[u][0], Z + X - (dp[v][0] - a[v]) + max(dp[v][0], dp[v][2]));
		X = max(X, -(dp[v][0] - a[v]) + dp[v][2]);
	}

	dp[u][0] = max(dp[u][0], Y);
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		adj[i].clear();
		cin >> a[i];
	}

	for(int i = 0; i < n; ++i) cin >> t[i];

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 0);

	cout << dp[0][0] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

