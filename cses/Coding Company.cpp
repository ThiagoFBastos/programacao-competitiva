#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;
 
const int mod = 1e9 + 7, N = 1e4 + 1, skip = 5000;
 
int mod_sum(i64 x) {
	if(x >= (mod << 1)) return x % mod;
	return x >= mod ? x - mod : x;
}
 
int dp[2][N][52];
 
void solve() {
	int n, x;
	
	cin >> n >> x;
	
	vector<int> t(n);
	
	for(int& v : t) cin >> v;
	
	sort(t.begin(), t.end());
	
	dp[0][skip][0] = 1;
	
	x += skip;
	
	for(int i = 0; i < n; ++i) {
		int m = min(i, n / 2);
		for(int k = 0; k <= x; ++k) {
			for(int j = 0; j <= m; ++j) {
				dp[1][k][j] = dp[0][k][j];
				dp[0][k][j] = 0;
			}
		}
		for(int k = x; k >= 0; --k) {
			for(int j = 0; j <= m; ++j) {
				int v = dp[1][k][j], a = k + t[i], b = k - t[i];
				if(j && a <= x) dp[0][a][j - 1] = mod_sum(dp[0][a][j - 1] + 1ll * j * v);
				if(b >= 0) dp[0][b][j + 1] = mod_sum(dp[0][b][j + 1] + v);
				dp[0][k][j] = mod_sum(dp[0][k][j] + (j + 1ll) * v);
			}
		}
	}
	
	i64 ans = 0;
	for(int i = 0; i <= x; ++i) ans = mod_sum(ans + dp[0][i][0]);
	
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
