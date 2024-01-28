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

const int MOD = 1e9 + 7;

void solve() {
	int n, m, c;
	cin >> n >> m >> c;
	vector<vector<ii>> adj(n);
	vector<int> dp(c + 1, 0), cost(n, -1);
	for(int i = 0; i < m; ++i) {
		int a, b, c;	
		cin >> a >> b >> c;
		--a, --b;
		adj[b].pb({a, c});
	}
	cost[0] = 1;
	auto dfs = [&](auto& self, int u)->void {
		cost[u] = 0;
		for(auto [v, w] : adj[u]) {
			if(cost[v] < 0) self(self, v);
			cost[u] = min(cost[u] + cost[v] + w, c + 1);
		}
	};
	dp[0] = 1;
	vector<int> p(c + 1);
	for(int i = 0; i < n; ++i) {
		if(cost[i] < 0) dfs(dfs, i);
		fill(all(p), 0);
		for(int j = 0; j + cost[i] <= c; ++j) {
			int k = j + cost[i];
			p[k] += dp[j];
			if(p[k] >= MOD) p[k] -= MOD;
			p[k] += p[j];
			if(p[k] >= MOD) p[k] -= MOD;
		}
		for(int j = 0; j <= c; ++j) {
			dp[j] += p[j];
			if(dp[j] >= MOD) dp[j] -= MOD;
		}
	}
	int ans = 0;
	for(int i = 1; i <= c; ++i) {
		ans += dp[i];
		ans %= MOD;
	}
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

