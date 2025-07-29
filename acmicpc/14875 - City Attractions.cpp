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
using i128 = __int128;

const int N = 3e5 + 10;

vector<int> adj[N];
pair<i64, int> dp[N];
int depth[N], a[N], sp[2][N], n;
i64 k;

void dfs(int u, int p) {
	dp[u] = {-INFLL, 0};
	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);			
		dp[u] = max(dp[u], max(dp[v], {a[v] - depth[v], -v}));
	}
}

void getNext(int u, int p, pair<i64, int> best) {
	pair<i64, int> nxt[2];

	nxt[0] = {a[u] - depth[u], -u};
	nxt[1] = {-INFLL, 0};

	for(int v : adj[u]) {
		if(v == p) continue;
		auto DP = max(dp[v], {a[v] - depth[v], -v});
		if(nxt[0] < DP) nxt[1] = nxt[0], nxt[0] = DP;
		else nxt[1] = max(nxt[1], DP);
	}

	auto k1 = best;
	auto k2 = dp[u];
	k1.fi -= depth[u], k2.fi += depth[u];
	sp[0][u] = -max(k1, k2).sc;

	for(int v : adj[u]) {
		if(v == p) continue;
		auto DP = max(dp[v], {a[v] - depth[v], -v});
		auto choise = nxt[DP == nxt[0]];
		choise.fi += 2 * depth[u];
		getNext(v, u, max(choise, best));
	}
}

void solve() {
	cin >> n >> k;

	for(int i = 0; i < n; ++i) cin >> a[i];

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs(0, -1);
	getNext(0, -1, {-INFLL, 0});
	
	int s = 0;

	for(int i = 0; i < 64; ++i, k /= 2) {
		if(k & 1) s = sp[0][s];
		for(int j = 0; j < n; ++j) sp[1][j] = sp[0][sp[0][j]];
		for(int j = 0; j < n; ++j) sp[0][j] = sp[1][j];		
	}

	cout << s + 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
