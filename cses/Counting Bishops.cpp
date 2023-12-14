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
 
const int N = 501, MOD = 1e9 + 7;
 
int dp[2][N * N];
 
void solve() {
	int n, k;
 
	cin >> n >> k;
 
	vector<int> d[2];
 
	for(int i : {1, 2}) {
		for(int k = i; k < n; k += 2) {
			d[i & 1].pb(k);
			d[i & 1].pb(k);
		}
		sort(all(d[i & 1]));
	}
 
	d[n & 1].pb(n);
 
	for(int i : {0, 1}) {
		dp[i][0] = 1;
		for(int j = 0; j < (int)d[i].size(); ++j)
			for(int k = j; k >= 0; --k)
				dp[i][k + 1] = (dp[i][k + 1] + dp[i][k] * (d[i][j] - k + 0ll)) % MOD;
	}
 
	int cnt = 0;
	
	for(int i = 0; i <= k; ++i)
		cnt = (cnt + 1ll * dp[0][i] * dp[1][k - i]) % MOD;
	
	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
