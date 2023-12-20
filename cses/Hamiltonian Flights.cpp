#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
typedef long long ll;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MOD = 1e9 + 7;
	int n, m;
	ll dp[1 << 20][20], G[20][20], N[20];
	memset(&G[0][0], 0, sizeof G);
	memset(N, 0, sizeof N);
	cin >> n >> m;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		++G[u][v];
		N[u] |= 1 << v;
	}
	int x = 1 << n;
	for(int k = 0; k < x; ++k)
		for(int v = 0; v < n; ++v)
			dp[k][v] = -1;
	queue<ii> S;
	dp[1][0] = 1;
	S.push({1, 0});
	while(!S.empty()) {
		int mask, v, R;
		mask = S.front().first;
		v = S.front().second;
		S.pop();
		R = ~mask & N[v];
		while(R) {
			int u, p = R & -R; 
			u = __builtin_ctz(p);
			if(dp[mask | p][u] == -1) {
				dp[mask | p][u] = dp[mask][v] * G[v][u] % MOD;
				S.push({mask | p, u});
			}
			else {
				dp[mask | p][u] += dp[mask][v] * G[v][u] % MOD;
				if(dp[mask | p][u] >= MOD) 
					dp[mask | p][u] -= MOD;
			}
			R -= p;
		}
	}
	cout << dp[x - 1][n - 1] << '\n';
	return 0;
}
