#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 21;
const int M = 2e5 + 100;
const int mod = 998244353;

i64 dp[N][M], fat[M], inv[M], invf[M];

i64 C(int n, int k) {
	return fat[n]*invf[n-k]%mod*invf[k]%mod;
}

void solve() {

	int n, m;
	i64 ans = 0;

	cin >> m >> n;

	dp[1][1] = 1;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= m; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod%i]%mod;
		invf[i]=invf[i-1]*inv[i]%mod;
	}

	for(int i = 2; (1 << (i - 1)) <= n; ++i) {
		for(int j = 1 << (i - 2); j <= n; ++j) {
			for(int k = 2; k * j <= n; ++k) {
				dp[i][k * j] += dp[i - 1][j];
				if(dp[i][k * j] >= mod) dp[i][k * j] -= mod;				
			}
		}
	}

	for(int i = 1; (1 << (i - 1)) <= n; ++i) {
		if(i > m) break;
		for(int k = 1; k <= n; ++k) {
			i64 ways = C(m - 1, i - 1) * dp[i][k] % mod * (n / k);
			ans = (ans + ways) % mod;
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
