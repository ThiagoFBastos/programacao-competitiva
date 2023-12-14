#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
long long fat[501], inv[501], invfat[501], dp[500][500];
int mod_sum(int a) {
	return a >= mod ? a - mod : a;
}
auto C(int n, int k) {
	return fat[n] * invfat[n - k] % mod * invfat[k] % mod;
}
void solve() {
	string s;
	cin >> s;
	int n = size(s);
	if(n % 2) {
		cout << "0\n";
		return;
	}
	for(int i = 0; i < n - 1; ++i) if(s[i] == s[i + 1]) dp[i][i + 1] = 1;
	for(int m = 4; m <= n; m += 2) {
		for(int i = 0; i <= n - m; ++i) {
			if(s[i] == s[i + m - 1]) dp[i][i + m - 1] = dp[i + 1][i + m - 2];
			for(int j = i + 1; j < i + m - 1; j += 2) {
				if(s[i] == s[j]) {
					auto L = j - i == 1 ? 1 : dp[i + 1][j - 1];
					dp[i][i + m - 1] = mod_sum(dp[i][i + m - 1] + L * dp[j + 1][i + m - 1] % mod * C(m / 2, (j - i + 1) / 2) % mod);
				}
			}
		}
	}
	cout << dp[0][n - 1] << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invfat[k] = 1;
	for(int k = 2; k <= 500; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = mod_sum(-(mod / k) * inv[mod % k] % mod + mod);
		invfat[k] = inv[k] * invfat[k - 1] % mod;
	}
	solve();
	return 0;
}
