#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
int n, m;
int get(int mask) {
	for(int i = 0; i < n; ++i) {
		if(mask & 1 << i) {
			if(i == n - 1 || !(mask & 1 << i + 1)) return 0;
			++i;
		}
	}
	return 1;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);	
	cin >> n >> m;
	if(n > m) swap(n, m);
	vector<int> g(1 << n);
	vector<vector<int>> dp(m, vector<int>(1 << n));
	for(int i = 0; i < (1 << n); ++i) dp[0][i] = get(i);
	for(int i = 1; i < m; ++i) {
		fill(g.begin(), g.end(), 0);
		for(int j = 0; j < (1 << n); ++j) {
			int k = ~j & ((1 << n) - 1);
			g[k] += dp[i - 1][j];
			if(g[k] >= mod) g[k] -= mod;
		}
		for(int j = 0; j < n - 1; ++j) {
			for(int k = 0; k < (1 << n); ++k) {
				if(!(k & 1 << j) && !(k & 1 << (j + 1))) {
					int mask = k ^ (1 << j) ^ (1 << (j + 1));
					g[mask] += g[k];
					if(g[mask] >= mod) g[mask] -= mod;
				}
			}
		}
		for(int j = 0; j < (1 << n); ++j) dp[i][j] = g[j];
	}
	cout << dp[m - 1][(1 << n) - 1] << '\n';
 	return 0;
}
