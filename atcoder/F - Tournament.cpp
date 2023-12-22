#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

const int N = 16;

int n;

i64 c[(1<<N)+1][N+1], dp[N+1][(1<<N)+1];

void DP(int k, int l, int r) {
	if(k == 0) return;

	int m = (l + r) / 2;

	DP(k - 1, l, m);
	DP(k - 1, m + 1, r);

	i64 best[2] = {0};

	for(int i = l; i <= m; ++i) best[0] = max(best[0], dp[k - 1][i] + c[i][k - 1]);
	for(int i = m + 1; i <= r; ++i) best[1] = max(best[1], dp[k - 1][i] + c[i][k - 1]);
	for(int i = l; i <= m; ++i) dp[k][i] = dp[k - 1][i] + best[1];
	for(int i = m + 1; i <= r; ++i) dp[k][i] = dp[k - 1][i] + best[0];
}

void solve() {
	i64 ans = 0;

	cin >> n;

	for(int i = 1; i <= (1 << n); ++i)
		for(int j = 1; j <= n; ++j)
			cin >> c[i][j];
	
	DP(n, 1, 1 << n);

	for(int i = 1; i <= (1 << n); ++i) ans = max(ans, dp[n][i] + c[i][n]);

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
