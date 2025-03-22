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

const int N = 1e3 + 10, MOD = 1e9 + 7;
ii dp[2][N][N];

ii cmp(ii a, ii b, int x = 0) {
	b.fi += x;
	if(a.fi != b.fi) return max(a, b);
	a.sc += b.sc;
	if(a.sc >= MOD) a.sc -= MOD;
	return a;
}

void solve() {
	int n, k;

	cin >> n >> k;

	vector<int> c(n);

	for(int& v : c) cin >> v;

	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < k; ++j)
			dp[0][i][j] = {-INF, 0};

	dp[0][1][k - 1] = {0, 1};

	for(int i = 0; i < n; ++i) {
		for(int a = 1; a <= n; ++a)
			for(int b = 0; b < k; ++b)
				dp[1][a][b] = {-INF, 0};
		for(int a = 1; a <= n; ++a) {
			for(int b = 0; b < k; ++b) {
				if(b < k - 1 && a == c[i]) dp[1][a][b + 1] = cmp(dp[1][a][b + 1], dp[0][a][b], 1);
				if(b == k - 1) dp[1][c[i]][0] = cmp(dp[1][c[i]][0], dp[0][a][b], 1);
			}
		}
		for(int a = 1; a <= n; ++a)
			for(int b = 0; b < k; ++b)
				dp[0][a][b] = cmp(dp[0][a][b], dp[1][a][b]);
	}

	ii ans = {0, 0};

	for(int i = 1; i <= n; ++i) ans = cmp(ans, dp[0][i][k - 1]);

	cout << ans.sc << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
