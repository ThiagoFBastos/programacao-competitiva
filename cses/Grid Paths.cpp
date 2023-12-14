#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
int mod_sum(int x) {
	if(x >= mod) return x - mod;
	else if(x < 0) return x + mod;
	return x;
}
void solve() {
	int n, m;
	cin >> n >> m;
	vector<long long> fat(2 * n + 1), inv(2 * n + 1), invfat(2 * n + 1), dp(m);
	vector<pair<int, int>> p(m);
	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invfat[i] = 1;
	for(int i = 2; i <= 2 * n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = mod_sum(-(mod / i) * inv[mod % i] % mod + mod);
		invfat[i] = inv[i] * invfat[i - 1] % mod;
	}
	auto C = [&fat, &invfat](int n, int k) {
		return fat[n] * invfat[n - k] % mod * invfat[k] % mod;
	};
	for(int i = 0; i < m; ++i) cin >> p[i].first >> p[i].second;
	sort(p.begin(), p.end());
	for(int i = 0; i < m; ++i) dp[i] = C(p[i].first + p[i].second - 2, p[i].first - 1);
	for(int i = 0; i < m; ++i) {
		auto [x0, y0] = p[i];
		for(int j = i + 1; j < m; ++j) {
			auto [x1, y1] = p[j];
			if(x0 <= x1 && y0 <= y1) dp[j] = mod_sum(dp[j] - dp[i] * C(x1 + y1 - x0 - y0, x1 - x0) % mod);
		}
	}
	int ans = C(2 * n - 2, n - 1);
	for(int i = 0; i < m; ++i) ans = mod_sum(ans - dp[i] * C(2 * n - p[i].first - p[i].second, n - p[i].first) % mod);
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
