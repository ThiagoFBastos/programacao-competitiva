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

const int N = 81, K = 25600, zero = 12720;

int a[N][N], b[N][N];

bitset<K> dp[N][N];

void solve() {
	
	int h, w, ans = INT_MAX;

	cin >> h >> w;

	for(int i = 0; i < h; ++i)
	for(int j = 0; j < w; ++j)
		cin >> a[i][j];	

	for(int i = 0; i < h; ++i)
	for(int j = 0; j < w; ++j)
		cin >> b[i][j];

	dp[0][0][zero] = 1;

	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			int x = abs(a[i][j] - b[i][j]);
			dp[i + 1][j] = dp[i + 1][j] | (dp[i][j] << x) | (dp[i][j] >> x);
			dp[i][j + 1] = dp[i][j + 1] | (dp[i][j] << x) | (dp[i][j] >> x);
		}
	}

	for(int i = 0; i < K; ++i) if(dp[h - 1][w][i]) ans = min(ans, abs(zero - i));
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
