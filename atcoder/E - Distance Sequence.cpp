#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int mod = 998244353;
const int N = 5100;

array<int, N> dp[2];

void solve() {
	int n, m, k;

	cin >> n >> m >> k;

	fill(dp[0].begin(), dp[0].end(), 0);

	for(int i = 1; i <= m; ++i) dp[0][i] = 1;	

	for(int i = 1; i < n; ++i) {
		for(int j = 0; j <= m; ++j) dp[1][j] = 0;

		for(int j = 1; j <= m; ++j) {
			dp[0][j] += dp[0][j - 1];
			if(dp[0][j] >= mod) dp[0][j] -= mod;
		}

		for(int j = 1; j <= m; ++j) {
			dp[1][j] = dp[0][m];
			int l = max(0, j - k), r = min(m, j + k - 1);	
			if(l > r) continue;
			int X = dp[0][r] - dp[0][l];
			if(X < 0) X += mod;
			dp[1][j] -= X;			
			if(dp[1][j] < 0) dp[1][j] += mod;
		}

		swap(dp[0], dp[1]);
	}

	for(int j = 1; j <= m; ++j) {
		dp[0][j] += dp[0][j - 1];
		if(dp[0][j] >= mod) dp[0][j] -= mod;
	}

	cout << dp[0][m] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
