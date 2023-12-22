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

const int mod = 1e9 + 7, N = 64, K = 2600;

array<array<int, K>, N> dp[2];

void solve() {

	int n, k, s;

	cin >> n >> k;

	s = n * n;

	for(int i = 0; i <= n; ++i)
	for(int j = 0; j <= s; ++j)
		dp[0][i][j] = 0;

	dp[0][0][0] = 1;

	for(int i = n; i; --i) {
		// i

		for(int a = 0; a <= n; ++a)
		for(int b = 0; b <= s; ++b)
			dp[1][a][b] = 0;

		// i - pi
		for(int a = 0; a <= n; ++a) {
			for(int b = 0; b <= s; ++b) {
				dp[1][a + 1][b + i] += dp[0][a][b];
				if(dp[1][a + 1][b + i] >= mod) dp[1][a + 1][b + i] -= mod;
			}
		}
	
		// pi - i

		for(int a = 1; a <= n; ++a) {
			for(int b = i; b <= s; ++b) {
				int X = (i64)dp[0][a][b] * a % mod;
				dp[1][a][b - i] += X;
				if(dp[1][a][b - i] >= mod) dp[1][a][b - i] -= mod;
			}
		}

		
		swap(dp[0], dp[1]);

		// pi

		for(int a = 0; a <= n; ++a)
		for(int b = 0; b <= s; ++b)
			dp[1][a][b] = 0;

		// pi - i
		for(int a = 1; a <= n; ++a) {
			for(int b = 0; b <= s; ++b) {
				dp[1][a][b + i] += dp[0][a][b];
				if(dp[1][a][b + i] >= mod) dp[1][a][b + i] -= mod;
			}
		}

		// i - pi
		for(int a = 1; a <= n; ++a) {
			for(int b = i; b <= s; ++b) {
				int X = (i64)dp[0][a][b] * a % mod;
				dp[1][a - 1][b - i] += X;
				if(dp[1][a - 1][b - i] >= mod) dp[1][a - 1][b - i] -= mod;
			}
		}

		swap(dp[0], dp[1]);
	}

	cout << dp[0][0][k] << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(t--) solve();
}
