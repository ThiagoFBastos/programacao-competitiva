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

const int mod = 1e9 + 7, N = 3002;

int dp[N][N];

void solve() {
	
	int n;

	cin >> n;

	vector<i64> a(n + 1, 0);

	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	
	dp[0][0] = 1;

	for(int i = 1; i < n; ++i) {
		for(int j = i; j; --j) {
			int x = a[i] % j;
			int y = a[i] % (j + 1);
			dp[j][y] += dp[j - 1][x];
			if(dp[j][y] >= mod) dp[j][y] -= mod;
		}
	}

	int ans = 0;

	for(int j = 1; j <= n; ++j) {
		int x = a[n] % j;
		ans += dp[j - 1][x];
		if(ans >= mod) ans -= mod;
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

