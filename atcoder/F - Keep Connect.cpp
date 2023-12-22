#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 3010;

array<int, MAXN> dp[2][2];

void solve() {
	int n, p;

	cin >> n >> p;

	for(int i = 0; i < 2; ++i) dp[0][i].fill(0);

	dp[0][0][0] = 1;
	dp[0][1][1] = 1;	

	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < 2; ++j) dp[1][j].fill(0);
	
		for(int j = 0; j < n; ++j) {

			// 0 -> 0

			dp[1][0][j] = (dp[1][0][j] + dp[0][0][j]) % p;
			dp[1][0][j + 1] = (dp[1][0][j + 1] + 3ll * dp[0][0][j]) % p;
			

			// 1 -> 1

			dp[1][1][j + 1] = (dp[1][1][j + 1] + dp[0][1][j]) % p;

			// 0 -> 1

			dp[1][1][j + 2] = (dp[1][1][j + 2] + 2ll * dp[0][0][j]) % p;

			// 1 -> 0

			dp[1][0][j] = (dp[1][0][j] + dp[0][1][j]) % p;
		}

		for(int j = 0; j < 2; ++j) swap(dp[0][j], dp[1][j]);
	}

	for(int i = 1; i < n; ++i) cout << dp[0][0][i] << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
