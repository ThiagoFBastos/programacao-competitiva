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

const int N = 5e3 + 10, MOD = 1e9 + 7;

ii dp[N][N];

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

	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < k; ++j) dp[i][j] = {-INF, 0};
		dp[i][0] = {0, 1};
	}

	ii ans = {0, 1};

	for(int i = 0; i < n; ++i) {
		ii x = dp[c[i]][k - 1];
		ans = cmp(ans, x, 1);
		for(int j = k - 2; j >= 0; --j) dp[c[i]][j + 1] = cmp(dp[c[i]][j + 1], dp[c[i]][j], 1);
		for(int j = 1; j <= n; ++j) dp[j][0] = cmp(dp[j][0], x, 1);
	}

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
