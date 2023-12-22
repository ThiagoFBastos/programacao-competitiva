#include "bits/stdc++.h"
using namespace std;

const long long INF = 1e15L;
const int N = 302;
long long dp[N][N];

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> h(n + 2, 0);
	for(int i = 1; i <= n; ++i) cin >> h[i];
	++n;
	for(int i = 0; i <= n; ++i)
	for(int j = 0; j <= m; ++j)
		dp[i][j] = INF;
	dp[0][0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < i; ++j)
			for(int k = 0; k + i - j - 1 <= m; ++k)
				dp[i][k + i - j - 1] = min(dp[i][k + i - j - 1], max(h[i] - h[j], 0) + dp[j][k]);
	auto ans = INF;
	for(int k = 0; k <= m; ++k) ans = min(ans, dp[n][k]);
	cout << ans << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
