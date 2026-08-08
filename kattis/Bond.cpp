#include <bits/stdc++.h>

using namespace std;

int g[20][20];

void solve() {
	int n;
	cin >> n;

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		cin >> g[i][j];
		
	vector<double> dp(1 << n, 0);
	dp[0] = 1;
	
	for(int i = 0; i < (1 << n); ++i) {
		int k = __builtin_popcount(i);
		for(int j = 0; j < n; ++j) {
			if(i & 1 << j) continue;
			dp[i | 1 << j] = max(dp[i | 1 << j], dp[i] * g[k][j] / 100.0);
		}
	}
	
	cout << fixed << setprecision(12) << 100.0 * dp.back() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}