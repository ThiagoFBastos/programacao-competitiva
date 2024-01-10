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

int n, m;
vector<vector<int>> g;
vector<int> a, dp;

void dfs(int v) {
	dp[v] = INT_MIN;
	for(int u : g[v]) {
		if(dp[u] == -1) dfs(u);
		dp[v] = max(dp[v], max(dp[u], a[u]));
	}
}

void solve() {
	cin >> n >> m;

	a.resize(n);
	g.resize(n);
	dp.assign(n, -1);

	for(int& v : a) cin >> v;

	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		--x, --y;
		g[x].push_back(y);
	}

	for(int i = 0; i < n; ++i) {
		if(dp[i] != -1) continue;
		dfs(i);
	}

	int ans = INT_MIN;

	for(int i = 0; i < n; ++i) ans = max(ans + 0LL, 1LL * dp[i] - a[i]);

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

