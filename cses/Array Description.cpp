#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
#define MOD 1000000007
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, a[MAXN], **dp;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) cin >> a[i];
	dp = new int*[n];
	for(int i = 0; i <= n; ++i) {
		dp[i] = new int[m + 2];
		for(int j = 0; j <= m + 1; ++j)
			dp[i][j] = 0;
	}
	if(a[0])
		dp[0][a[0]] = 1;
	else
		for(int i = 1; i <= m; ++i) 
			dp[0][i] = 1;
 	for(int i = 1; i < n; ++i) {
		if(a[i])
			dp[i][a[i]] = (0LL + dp[i - 1][a[i] - 1] + dp[i - 1][a[i]] + dp[i - 1][a[i] + 1]) % MOD;
		else 
			for(int k = 1; k <= m; ++k) 
				dp[i][k] = (0LL + dp[i - 1][k - 1] + dp[i - 1][k] + dp[i - 1][k + 1]) % MOD;
	}
	ll r = 0;
	if(a[n - 1]) 
		r = dp[n - 1][a[n - 1]];
	else {
		for(int i = 1; i <= m; ++i) 
			r += dp[n - 1][i];
		r %= MOD;
	}
	cout << r << '\n';
	return 0;
} 
