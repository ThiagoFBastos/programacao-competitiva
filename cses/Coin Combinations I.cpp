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
 
	vi c(n);
	ll *dp;
 
	posix_memalign((void**)&dp, 64, (x + 1) * sizeof(ll));
 
	memset(dp, 0, (x + 1) * sizeof(ll));
 
	for(int k = 0; k < n; ++k)
		cin >> c[k];
 
	sort(c.begin(), c.end());
	
	dp[0] = 1;
 
	for(int k = c[0]; k <= x; ++k) {
 
		ll X = 0;
 
		for(int i = 0; i < n && c[i] <= k; ++i)
			X += dp[k - c[i]];
 
		dp[k] = X % MOD;
	}
	
	cout << dp[x] << '\n';
	
	return 0;
}
