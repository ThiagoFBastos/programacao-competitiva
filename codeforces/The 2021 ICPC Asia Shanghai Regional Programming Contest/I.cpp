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

const int N = 102, K = 6e3, skip = 2600;
const i64 INF = 1e15L;

i64 dp[N][K];

void solve() {
	int n, k;

	cin >> n >> k;

	vector<int> v(n), t(n);

	for(int i = 0; i < n; ++i) cin >> v[i] >> t[i];

	for(int i = 0; i <= k; ++i)	
	for(int j = 0; j < K; ++j)
		dp[i][j] = -INF;

	dp[0][skip] = 0;

	for(int l = 0; l < n; ++l) {
		for(int i = k; i >= 0; --i) {
			vector<i64> value(K, -INF); 
			for(int j = -2600; j <= 2600; ++j) {
				for(int m : {-1, 1}) {
					int X = m * t[l] + j;
					if(X <= 2600 && X >= -2600) 
						value[X + skip] = max(value[X + skip], dp[i][j + skip] + v[l]);
				}
				for(int m : {-2, 2}) {
					int X = m * t[l] + j;
					if(X <= 2600 && X >= -2600) 
						dp[i + 1][X + skip] = max(dp[i + 1][X + skip], dp[i][j + skip] + v[l]);
				}
			}
			for(int j = -2600; j <= 2600; ++j)
				dp[i][skip + j] = max(dp[i][skip + j], value[skip + j]);
		}
	}

	i64 ans = -INF;
	for(int i = 0; i <= k; ++i) ans = max(ans, dp[i][skip]);
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

