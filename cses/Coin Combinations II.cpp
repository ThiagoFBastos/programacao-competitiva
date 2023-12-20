#include <bits/stdc++.h>
 
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using ii = pair<int, int>;
 
#define MOD 1000000007
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 
	int n, x;
	
	cin >> n >> x;
 
	vi c(n), dp(x + 1);
	
	for(int k = 0; k < n; ++k)
		cin >> c[k];
 
	dp[0] = 1;
 
	for(int k = 0; k < n; ++k) {
 
		int N = x - c[k], y = c[k];
 
		for(int j = 0; j <= N; ++j)
			dp[y + j] = (dp[j] + dp[y + j]) % MOD;
	}
 
	cout << dp[x] << '\n';
 
	return 0;
}
