#include "bits/stdc++.h"
 
using namespace std;
 
#define INF   1000000000
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
using i128 = __int128;
 
const int N = 5e3 + 10, MOD = 1e9 + 7;
 
int f[N][N], c[N][N], dp[N], pt[N];
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	f[0][0] = c[0][0] = pt[0] = 1;
 
	for(int i = 1; i <= n; ++i) pt[i] = (i64)n * pt[i - 1] % MOD;
 
	for(int i = 1; i <= n; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			if(c[i][j] >= MOD) c[i][j] -= MOD;
		}
		for(int j = 1; j <= n; ++j) 
			f[i][j] = ((j - 1ll) * f[i][j - 1] + f[i - 1][j - 1]) % MOD;
	}
 
	for(int i = n; i; --i)
		for(int j = 1; j <= n; ++j) 
			dp[i] = (dp[i] + (i64)f[i][j] * c[n][j] % MOD * pt[n - j]) % MOD;
	
	for(int i = n; i; --i) {
		dp[i] = (dp[i] + MOD) % MOD;
		for(int j = i - 1; j; --j)
			dp[j] = (dp[j] - (i64)dp[i] * c[i][j]) % MOD;
	}
 
	for(int i = 1; i <= n; ++i) cout << dp[i] << '\n';
 
	return 0;
}
