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

const int mod = 998244353, N = 320;

int dp[N][N], v[N];

void solve() {
	
	int n, m;

	cin >> n >> m;
	
	vector<ii> a(n);

	for(auto& [p, q] : a) cin >> p;
	for(auto& [p, q] : a) cin >> q;

	sort(a.begin(), a.end());

	dp[0][301] = 1;

	for(int i = 0; i < n; ++i) {
		auto [p, q] = a[i];
		for(int k = m; k >= 0; --k) {
			for(int j = q; j <= 301; ++j) {
				dp[k + 1][j] += dp[k][j];
				if(dp[k + 1][j] >= mod) dp[k + 1][j] -= mod;
			}
			memset(v, 0, sizeof(int) * 302);
			for(int j = q; j <= 301; ++j) {
				int u = min(j, q);
				v[u] += dp[k][j];
				if(v[u] >= mod) v[u] -= mod;
			}
			for(int j = q; j <= 301; ++j) dp[k][j] = v[j];
		}
	}

	int ans = 0;
	for(int i = 0; i <= 301; ++i) ans = (ans + dp[m][i]) % mod;
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
