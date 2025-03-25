#pragma GCC optimize("O3")

#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7, maxn = 1e2 + 1;

int dp[maxn][maxn];
long long fat[maxn], inv[maxn], invfat[maxn];

int mod_sum(int x) {
	return x >= mod ? x - mod : x;
}

void solve() {
	int n, d;
	
	cin >> n >> d;
	
	if(n <= 2) {
		cout << "1\n";
		return;
	}
		
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invfat[k] = 1;
	
	for(int k = 2; k <= n; ++k) {
		fat[k] = fat[k - 1] * k % mod;
		inv[k] = mod_sum(-(mod / k) * inv[mod % k] % mod + mod);
		invfat[k] = invfat[k - 1] * inv[k] % mod;
	}
	
	dp[0][0] = fat[n - 2];
	
	for(int i = 1; i <= n; ++i)
		for(int k = 0; k <= n; ++k)
			for(int j = 0; j < d && k + j <= n; ++j)
				dp[i][k + j] = mod_sum(dp[i][k + j] + dp[i - 1][k] * invfat[j] % mod);
	
	cout << dp[n][n - 2] << '\n';
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}