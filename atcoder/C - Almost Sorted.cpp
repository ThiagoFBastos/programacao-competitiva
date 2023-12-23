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

const int N = 510, MOD = 998244353;

int dp[N][1<<11], tmp[1<<11];

void solve() {
	int n, d;
	cin >> n >> d;
	vector<int> a(n), f;
	vector<bool> vis(n + 1, false);
	for(int& v : a) {
		cin >> v;
		if(v < 0) continue;
		vis[v] = true;
	}	
	for(int i = 1; i <= n; ++i) if(!vis[i]) f.pb(i);
	dp[0][0] = 1;
	int lo = 0, len = 2 * d + 1;
	for(int i = 1; i <= n; ++i) {
		int mask = 0;
		while(lo < (int)f.size() && f[lo] - d <= i) {
			mask |= 1 << (f[lo] + d - i);
			++lo;
		}
		memset(tmp, 0, sizeof tmp);
		for(int j = 0; j < (1 << len); ++j) tmp[j | mask] += dp[i - 1][j];
		memcpy(dp[i], tmp, sizeof tmp);
		if(a[i - 1] == -1) {
			memset(tmp, 0, sizeof tmp);
			for(int j = 0; j < (1 << len); ++j) {
				for(int k = j; k; k -= k & -k) {
					int l = __builtin_ctz(k);
					int mask = j ^ (1 << l);
					tmp[mask] += dp[i][j];
					if(tmp[mask] >= MOD) tmp[mask] -= MOD;
				}
			}
			memcpy(dp[i], tmp, sizeof tmp);
		}
		for(int j = 0; j < (1 << len); ++j) dp[i][j] = 2 * j < (1 << len) ? dp[i][2 * j] : 0; 
	}
	cout << dp[n][0] << '\n';
}
	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
