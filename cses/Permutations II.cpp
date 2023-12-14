#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 1e3 + 10, MOD = 1e9 + 7;
 
array<int, N> dp[2][2];
 
void solve() {
	int n;
 
	cin >> n;
 
	for(int i = 0; i < 2; ++i) dp[0][i].fill(0);
 
	dp[0][0][0] = 1;
 
	for(int i = 2; i <= n; ++i) {
 
		for(int k = 0; k < 2; ++k)
		for(int j = 0; j <= n; ++j)
			dp[1][k][j] = 0;
 
		for(int j = 0; j <= n; ++j) {
	
			dp[1][1][j + 1] = (dp[1][1][j + 1] + 2ll * dp[0][0][j]) % MOD;	
 
			if(j > 0) dp[1][0][j - 1] = (dp[1][0][j - 1] + 1ll * j * dp[0][0][j]) % MOD;	
 
			dp[1][0][j] = (dp[1][0][j] + 1ll * max(0, i - j - 2) * dp[0][0][j]) % MOD;
			
			dp[1][1][j] = (dp[1][1][j] + dp[0][1][j]) % MOD;
					
			dp[1][1][j + 1] = (dp[1][1][j + 1] + dp[0][1][j]) % MOD;
			 
			if(j) dp[1][0][j - 1] = (dp[1][0][j - 1] + (j - 1ll) * dp[0][1][j]) % MOD;
			 
			dp[1][0][j] = (dp[1][0][j] + 1ll * max(0, i - j - 1) * dp[0][1][j]) % MOD;
		}
 
		for(int k = 0; k < 2; ++k) swap(dp[0][k], dp[1][k]);
	}	
 
	cout << dp[0][0][0] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
