#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;	

const int mod = 998244353, N = 5001;

i64 fat[N], inv[N], invf[N];

i64 P(int n, int k) {
	if(n < k) return 0;
	return fat[n] * invf[n - k] % mod;
}

void solve() {
	int n, m;

	cin >> n >> m;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = inv[i] * invf[i - 1] % mod;
	}

	vector<int> cnt(m, 0), dp(n + 1, 0);
	
	for(int i = 1; i <= n; ++i) ++cnt[i % m];

	for(int i = 1; i <= n; ++i) {
		int v = 1;
		for(int j = 0; j < m; ++j) v = v * P(i, cnt[j]) % mod; 
		dp[i] = v;
	}
	
	for(int i = 1; i <= n; ++i) {
		dp[i] = dp[i] * invf[i] % mod;
		for(int j = i + 1; j <= n; ++j) {
			dp[j] -= dp[i] * P(j, i) % mod;
			if(dp[j] < 0) dp[j] += mod;
		}
		cout << dp[i] << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
