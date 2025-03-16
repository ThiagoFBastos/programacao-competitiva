#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
using vi = vector<int>;
using vvi = vector<vi>;
const int N = 6e3;
int dp[N][2];
void dfs(vvi& G, int u, int p) {
	dp[u][0] = 1;
	dp[u][1] = 0;
	for(int v : G[u]) {
		if(v != p)
			dfs(G, v, u);
	}
	for(int v : G[u]) {
		if(v != p) {
			dp[u][0] += dp[v][1];
			dp[u][1] += max(dp[v][0], dp[v][1]);
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		vvi G(n);
		for(int k = 1; k < n; ++k) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(G, 0, 0);
		cout << max(dp[0][0], dp[0][1]) << '\n';
	}
    return 0;
}