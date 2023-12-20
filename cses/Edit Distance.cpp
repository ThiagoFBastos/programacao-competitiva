#include "bits/stdc++.h"
using namespace std;
const int inf = 1e9;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s, t;
	int n, m;
	cin >> s >> t;
	n = s.size(), m = t.size();
	vector<vector<int>> dp(n + 2);
	for(int k = 0; k <= n + 1; ++k) dp[k].assign(m + 2, inf);
	dp[0][0] = 0;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= m; ++j) {
			dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (t[j] != s[i]));
			dp[i + 1][j] = min(dp[i + 1][j], 1 + dp[i][j]);
			dp[i][j + 1] = min(dp[i][j + 1], 1 + dp[i][j]);
		}
	}
	cout << dp[n][m] << '\n';
	return 0;
}
