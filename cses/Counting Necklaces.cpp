#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
long long exp(long long n, int p) {
	long long ans = 1;
	for( ; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a, dp;
	for(int k = 1; k * k <= n; ++k) {
		if(n % k) continue;
		a.push_back(k);
		if(n != k * k) a.push_back(n / k);
	}
	sort(a.begin(), a.end());
	dp.resize(a.size());
	for(int i = 0; i < int(a.size()); ++i) dp[i] = exp(m, a[i]);
	for(int i = 0; i < int(a.size()); ++i) {
		for(int j = i + 1; j < int(a.size()); ++j) {
			if(a[j] % a[i]) continue;
			dp[j] -= dp[i];
			if(dp[j] < 0) dp[j] += mod;
		}
	}
	int ans = 0;
	for(int i = 0; i < int(a.size()); ++i) ans = (ans + exp(a[i], mod - 2) * dp[i]) % mod;
	cout << ans << '\n';
	return 0;
}
