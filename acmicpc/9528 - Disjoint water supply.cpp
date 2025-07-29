#pragma GCC target("popcnt")
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

const int N = 1e3 + 10;

bitset<N> dp[N], par[N];
vector<int> adj[N];
int n, m, pairs;

vector<int> topoSort() {
	vector<bool> vis(n, false);
	vector<int> s;
	function<void(int)> dfs = [&](int u) {
		vis[u] = true;
		for(int v : adj[u]) {
			if(vis[v]) continue;
			dfs(v);
		}
		s.pb(u);
	};
	dfs(0);
	reverse(all(s));
	return s;
}

void solve() {

	cin >> n >> m;

	for(int i = 0; i < n; ++i) dp[i].set();

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
	}

	auto topo = topoSort();

	for(int u : topo) {
		par[u][u] = dp[u][u] = 1;	
		dp[u] &= par[u];
		for(int v : adj[u]) {
			dp[v] &= dp[u];
			par[v] |= par[u];
		}
	}

	for(int u = 0; u < n; ++u)
	for(int v = u + 1; v < n; ++v)
		pairs += (dp[u] & dp[v]).count() == 1;

	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}