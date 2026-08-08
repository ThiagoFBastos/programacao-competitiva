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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int inf = 1e9;
int dp[1 << 20][8];

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> a(n);

	for(int& v : a) cin >> v;
	
	for(int i = 0; i < (1 << n); ++i)
	for(int j = 0; j <= 7; ++j)
		dp[i][j] = inf;
		
	dp[0][0] = 0;
	
	int ans = inf;
	
	for(int i = 1; i < (1 << n); ++i) {
		for(int j = i; j; j -= j & -j) {
			int k = __builtin_ctz(j);
			for(int r = 0; r <= 7; ++r) {
				int x = min(r, a[k] - 1);
				int y = max(0, a[k] - x - 1);
				dp[i][y] = min(dp[i][y], dp[i ^ (1 << k)][r] + a[k] - x);
			}
		}
	}
	
	for(int r = 0; r <= 7; ++r) ans = min(ans, dp[(1 << n) - 1][r]);
	
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
