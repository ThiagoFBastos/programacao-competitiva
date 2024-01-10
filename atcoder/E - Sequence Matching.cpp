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

const int N = 1e3 + 1;

int dp[N][N];

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> a(n), b(m);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	for(int j = 0; j <= m; ++j) dp[0][j] = n + m;
	for(int i = 0; i <= n; ++i) dp[i][0] = n + m;

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] - 2;
			else dp[i][j] = dp[i - 1][j - 1] - 1;
			dp[i][j] = min(dp[i][j], min(dp[i - 1][j], dp[i][j - 1]));
		}
	}

	cout << dp[n][m] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

