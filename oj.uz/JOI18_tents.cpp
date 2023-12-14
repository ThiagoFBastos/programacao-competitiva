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
 
const int mod = 1e9 + 7, N = 3e3 + 1;
 
i64 dp[N][N];
 
int mod_sum(int x) {
	return x < mod ? x : x - mod;
}
 
void solve() {
	int h, w, ans = 0;
	
	cin >> h >> w;
	
	dp[h][w] = 1;
	
	for(int x = h; x >= 0; --x) {
		for(int y = w; y >= 0; --y) {
		
			if(x > 0 && y >= 2) {
				i64 ways = y * (y - 1LL) / 2 % mod * dp[x][y] % mod;
				dp[x - 1][y - 2] = (dp[x - 1][y - 2] + ways) % mod;
				ans = mod_sum(ans + ways);
			}
			
			if(x >= 2 && y > 0) {
				i64 ways = dp[x][y] * (x - 1) % mod * y % mod;
				dp[x - 2][y - 1] = (dp[x - 2][y - 1] + ways) % mod;
				ans = mod_sum(ans + ways);
			}
			
			if(x > 0 && y > 0) {
				i64 ways = 4LL * y * dp[x][y] % mod;
				dp[x - 1][y - 1] = (dp[x - 1][y - 1] + ways) % mod;
				ans = mod_sum(ans + ways);
			}
			
			if(x > 0) dp[x - 1][y] = mod_sum(dp[x - 1][y] + dp[x][y]);
		}
	}
	
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
