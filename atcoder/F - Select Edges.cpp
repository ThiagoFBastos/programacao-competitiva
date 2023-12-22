#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 3e5 + 100;
const i64 INF = 1e9 + 100;

vector<ii> g[N];
i64 dp[N][2];
int d[N], n;

void dfs(int u, int p = -1) {
	vector<i64> X;
	
	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		dp[u][1] += w + dp[v][0];
		X.push_back(dp[v][1] - w - dp[v][0]);
	}

	sort(X.rbegin(), X.rend());

	int m = (int)X.size() - d[u];

	for(int i = 0; i < m; ++i) dp[u][1] += X[i];

	dp[u][0] = dp[u][1];

	for(int i = max(0, m); i < (int)X.size(); ++i) {
		if(X[i] >= 0 || i == m) dp[u][0] += X[i];
		if(X[i] >= 0) dp[u][1] += X[i];
	}

	if(d[u] == 0) dp[u][0] = -INF;
}

void solve() {

	cin >> n;

	for(int i = 0; i < n; ++i) cin >> d[i];

	for(int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}

	dfs(0);

	cout << max(dp[0][0], dp[0][1]) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
