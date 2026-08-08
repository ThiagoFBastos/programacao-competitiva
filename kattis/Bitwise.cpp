#pragma GCC optimize("O3")
#pragma GCC target("popcnt","mmx","sse","sse2")

#include "bits/stdc++.h"
using namespace std;

struct sparse_table {
	vector<vector<int>> sp;
	sparse_table(vector<int>& a) {
		int n = size(a);
		int m = 32 - __builtin_clz(n);
		sp = vector<vector<int>>(m, vector<int>(n));
		for(int i = 0; i < n; ++i) sp[0][i] = a[i];
		for(int i = 1; i < m; ++i)
		for(int j = 0; j + (1 << i) - 1 < n; ++j)
			sp[i][j] = sp[i - 1][j] | sp[i - 1][j + (1 << (i - 1))];
	}
	int query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return sp[k][l] | sp[k][r - (1 << k) + 1];
	}
};

const int INF = 1e9, N = 1e6 + 1;

int pai[20][N];

void solve() {
	int n, m, k, mask = 0, maxn = 0;
	cin >> n >> k;
	vector<int> a(2 * n), dp(2 * n + 1);
	m = 32 - __builtin_clz(2 * n + 1);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		maxn = max(maxn, 31 - __builtin_clz(a[i]));
		a[i + n] = a[i];
	}
	sparse_table sp(a);
	dp[2 * n] = 0, pai[0][2 * n] = 2 * n;
	for(int i = maxn; i >= 0; --i) {
		int R = 2 * n - 1, S = mask | 1 << i;
		for(int j = 2 * n - 1; j >= 0; --j) {
			while(R > j && (sp.query(j, R - 1) & S) == S) --R; 
			dp[j] = (sp.query(j, R) & S) == S ? 1 + max(0, dp[R + 1]) : -INF;
			pai[0][j] = R + 1;
		}
		for(int i = 1; i < m; ++i)
		for(int j = 0; j < 2 * n + 1; ++j)
			pai[i][j] = pai[i - 1][pai[i - 1][j]];
		for(int j = 0; j < n; ++j) {
			if(dp[j] < k || pai[0][j] - j > n) continue;
			int v = j;
			for(int k = m - 1; k >= 0; --k) {
				int u = pai[k][v];
				if(pai[0][u] - j > n || dp[u] < 0) continue;
				v = u;
			}
			if(dp[j] - dp[v] + 1 >= k) {
				mask = S;
				break;	
			}
		}
	}
	cout << mask << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}