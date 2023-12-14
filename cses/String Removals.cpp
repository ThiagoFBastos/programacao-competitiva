#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 5e5, MOD = 1e9 + 7;
	string s;
	int dp[MAXN], n, R[26], x = 0;
	cin >> s;
	n = s.size();
	memset(R, 0, sizeof R);
	memset(dp, 0, sizeof(int) * n);
	for(int k = n - 1; k >= 0; --k) {
		int ch = s[k] - 'a';
		dp[k] += x + 1;
		if(dp[k] >= MOD) dp[k] -= MOD;
		dp[k] -= R[ch];
		if(dp[k] < 0) dp[k] += MOD;
		R[ch] += dp[k];
		if(R[ch] >= MOD) R[ch] -= MOD;
		x += dp[k];
		if(x >= MOD) x -= MOD;
	}
	cout << x << '\n';
	return 0;
}
