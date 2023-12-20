#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5, MOD = 1e9 + 7;
vector<int> G[MAXN];
int dp[MAXN];
void dfs(int v) {
	dp[v] = 0;
	for(int u : G[v]) {
		if(dp[u] == -1) dfs(u);
		dp[v] += dp[u];
		if(dp[v] >= MOD) dp[v] -= MOD;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;	
	memset(dp, -1, sizeof(int) * n);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
	}
	dp[n - 1] = 1;
	dfs(0);
	cout << dp[0] << '\n';
	return 0;
}
