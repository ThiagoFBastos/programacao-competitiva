#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 18, MOD = 1e9 + 7;
 
int dp[1 << N], pow2[1 << N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		++dp[x];
	}
 
	pow2[0] = 1;
	for(int i = 1; i <= n; ++i) {
		pow2[i] = pow2[i - 1] << 1;
		if(pow2[i] >= MOD)
			pow2[i] -= MOD;
	}
 
	for(int i = 0; i < N; ++i)
		for(int j = n; j >= 0; --j)
			if(~j & (1 << i))
				dp[j] += dp[j ^ (1 << i)];
 
	for(int i = 0; i <= n; ++i) {
		dp[i] = (pow2[dp[i]] - 1 + MOD) % MOD;
		if(__builtin_popcount(i) & 1)
			dp[i] = (MOD - dp[i]) % MOD;
	}
 
	for(int i = 0; i < N; ++i) {
		for(int j = n; j >= 0; --j) {
			if(~j & (1 << i)) {
				dp[j] += dp[j ^ (1 << i)];
				if(dp[j] >= MOD)
					dp[j] -= MOD;
			}
		}
	}
 
	for(int i = 0; i <= n; ++i) {
		int ans = dp[i];
 
		if(__builtin_popcount(i) & 1) {
			ans = MOD - ans;
			if(ans >= MOD)
				ans -= MOD;
		}
 
		cout << ans << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
