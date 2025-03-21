#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 2e3 + 10;

int dp[N][N], par[N], n, in[N], out[N], t;
vector<int> adj[N];
vector<ii> I[N];
string sym;

void dfs(int u, int p) {
	par[u] = p;
	in[u] = t++;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		I[u].pb({out[v], v});
	}
	out[u] = t - 1;
}

bool ancestral(int u, int v) {
	return in[v] >= in[u] && in[v] <= out[u];
}

int down(int u, int v) {
	auto it = lower_bound(all(I[u]), ii(in[v], -1));
	return it->sc;
}

int DP(int u, int v) {
	if(dp[u][v] != -1) return dp[u][v];

	dp[u][v] = 0;

	int nxtU = -1, nxtV = -1;

	if(ancestral(u, v)) {
		nxtU = down(u, v);
		nxtV = par[v];
	} else if(ancestral(v, u)) {
		nxtU = par[u];
		nxtV = down(v, u);
	} else {
		nxtU = par[u];
		nxtV = par[v];
	}
	
	if(sym[u] == sym[v]) dp[u][v] = max(dp[u][v], 2 + DP(nxtU, nxtV));

	dp[u][v] = max(dp[u][v], max(DP(nxtU, v), DP(u, nxtV)));

	return dp[u][v];
}

void solve() {
	cin >> n >> sym;

	for(int i = 0; i < n; ++i) {
		adj[i].clear();
		I[i].clear();
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v); adj[v].pb(u);
	}

	t = 0;
	dfs(0, 0);
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			dp[i][j] = -1;
			if((i == par[j] || j == par[i]) && sym[i] == sym[j]) dp[i][j] = 2;
		}
		dp[i][i] = 1;
	}

	int ans = 0;

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		ans = max(ans, DP(i, j));

	cout << ans << '\n';
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
