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

const int N = 301;

array<double, N> dp[2];

void solve() {
	
	int n;

	cin >> n;

	dp[0].fill(0);
	for(int i = 2; i <= n; ++i) dp[0][i] = 1.0 / (n - 1);

	for(int i = 2; i < n; ++i) {
		int f = n - i + 1;
		dp[1].fill(0);
		for(int k = 1; k <= n; ++k) {
			if(k == i) {
				for(int j = i + 1; j <= n; ++j) dp[1][j] += dp[0][k] / f;
			} else dp[1][k] += dp[0][k];
		}
		swap(dp[0], dp[1]);
	}

	cout << fixed << setprecision(12) << dp[0][n] << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}

