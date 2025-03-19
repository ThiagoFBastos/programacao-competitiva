#include "bits/stdc++.h"
using namespace std;
const long long inf = 1e14L;
double dp[1000][1000];
void solve() {
	int n;
	cin >> n;
	if(!n) {
		cout << fixed << setprecision(9) << 0.0 << '\n';
		return;
	}
	vector<tuple<int, int, int>> a(n);
	for(int i = 0; i < n; ++i) {
		int x, y, t;
		cin >> x >> y >> t;
		a[i] = {t, x, y};
	}
	sort(a.begin(), a.end());
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j) 
		dp[i][j] = inf;
	for(int i = 0; i < n; ++i) dp[0][i] = 0;
	for(int i = 1; i < n; ++i) {
		auto [t, x, y] = a[i];
		auto [t0, x0, y0] = a[i - 1];
		for(int j = 0; j < n; ++j) {
			auto [tj, xj, yj] = a[j];
			if(j == i) dp[i][i - 1] = min(dp[i][i - 1], dp[i - 1][i]);
			else {
				dp[i][i - 1] = min(dp[i][i - 1], max(dp[i - 1][j], hypot(x - xj, y - yj) / (t - tj)));
				dp[i][j] = min(dp[i][j], max(dp[i - 1][j], hypot(x - x0, y - y0) / (t - t0)));
			}
		}
	}
	auto ans = inf + 0.0;
	for(int i = 0; i < n; ++i) ans = min(ans, dp[n - 1][i]);
	cout << fixed << setprecision(9) << ans << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}