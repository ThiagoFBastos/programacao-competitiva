#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 1e2 + 10, MOD = 998244353;

int dp[N][N][N], a[N][N], first[N][3];

void solve() {
	int n;

	cin >> n;

	for(int i = 0; i <= n; ++i) {
		first[i][1] = INF;
		first[i][2] = -INF;
	}

	for(int i = 1; i <= n; ++i) {
		for(int j = i; j <= n; ++j) {
			int x;
			cin >> x;
			if(x == 1) first[j][x] = min(first[j][x], i);
			else first[j][x] = max(first[j][x], i);
		}
	}

	dp[0][0][0] = 1;

	for(int j = 1; j <= n; ++j) {

		for(int x = 0; x < j; ++x) {
			for(int y = 0; y < j; ++y) {
				dp[j][x][j] += dp[j - 1][x][y];
				dp[j][j][y] += dp[j - 1][x][y];
				if(dp[j][x][j] >= MOD) dp[j][x][j] -= MOD;
				if(dp[j][j][y] >= MOD) dp[j][j][y] -= MOD;
			}
		}

		for(int x = 0; x <= j; ++x) {
			for(int y = 0; y <= j; ++y) {
				int l = first[j][1];
				if(l != INF && min(x, y) >= l) dp[j][x][y] = 0;
				l = first[j][2];
				if(l != -INF && min(x, y) < l) dp[j][x][y] = 0;
			}
		}
	}

	int ans = 0;
	for(int x = 0; x <= n; ++x)
		for(int y = 0; y <= n; ++y)
			ans = (ans + dp[n][x][y]) % MOD;

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
