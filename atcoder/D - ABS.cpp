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

const int N = 2e3 + 10;

int dp[2][N], n, z, w, a[N];

void solve() {
	cin >> n >> z >> w;

	for(int i = 0; i < n; ++i) cin >> a[i];
	
	reverse(a, a + n);

	dp[0][1] = -INF;
	dp[1][1] = INF;
	dp[0][2] = dp[1][2] = abs(a[0] - a[1]);

	for(int i = 3; i <= n; ++i) {
		dp[1][i] = -INF;
		for(int j = 1; j < i; ++j) {
			dp[0][i] = max(dp[0][i], min(abs(a[j] - a[0]), dp[1][j]));
			dp[1][i] = min(dp[1][i], max(abs(a[j] - a[0]), dp[0][j]));	
		}
	}

	cout << max(abs(w - a[0]), dp[0][n]) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

