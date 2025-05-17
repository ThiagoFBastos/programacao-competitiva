#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 2e5 + 5, MOD = 1e9 + 7;
 
int dp[N], frq[N], pow2[N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		int val;
 
		cin >> val;
 
		++frq[val];
	}
 
	pow2[0] = 1;
	for(int i = 1; i <= n; ++i) {
		pow2[i] = pow2[i - 1] << 1;
		if(pow2[i] >= MOD)
			pow2[i] -= MOD;
	}
 
	for(int i = 1; i <= n; ++i) {
		for(int j = i; j <= n; j += i)
			dp[i] += frq[j];
 
		dp[i] = (pow2[dp[i]] - 1 + MOD) % MOD;;
	}
 
	for(int i = n; i >= 1; --i) {
		for(int j = 2 * i; j <= n; j += i) {
			dp[i] -= dp[j];
			if(dp[i] < 0)
				dp[i] += MOD;
		} 
	}
 
	for(int i = 1; i <= n; ++i)
		cout << dp[i] << ' ';
 
	cout << '\n';
	
	return 0;
}
