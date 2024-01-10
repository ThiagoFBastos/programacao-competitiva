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

const int N = 2e3 + 100, mod = 1e9 + 7;

int dp[N][N];

void solve() {
	int s, t, ans = 1;
	cin >> s >> t;

	vector<int> a(s), b(t);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	dp[0][0] = 1;

	for(int i = 0; i <= s; ++i) {
		for(int j = 0; j <= t; ++j) {
			if(i && j && a[i - 1] == b[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
				ans += dp[i - 1][j - 1];
				if(ans >= mod) ans -= mod;
			}
			if(i > 0) {
				dp[i][j] += dp[i - 1][j];
				if(dp[i][j] >= mod) dp[i][j] -= mod;
				if(j > 0) {
					dp[i][j] -= dp[i - 1][j - 1];
					if(dp[i][j] < 0) dp[i][j] += mod;
				}
			}
			if(j > 0) {
				dp[i][j] += dp[i][j - 1];
				if(dp[i][j] >= mod) dp[i][j] -= mod;
			}
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
