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

const int inf = 1e9, N = 1e4 + 1;
const i64 linf = 1e16L;

int col[N];
i64 dp[N];

void solve() {
	int n, k, l;

	cin >> n >> k >> l;

	vector<ii> a(n), b(k);

	for(auto& [x, y] : a) cin >> x >> y;
	for(auto& [x, y] : b) cin >> x >> y;

	fill(col, col + N, -inf);

	col[0] = 0;

	for(auto [x, y] : b)
		for(int k = N - x; k >= 0; --k)
			col[k + x] = max(col[k + x], col[k] + y);

	for(int i = 1; i < N; ++i) col[i] = max(col[i], col[i - 1]);

	fill(dp, dp + N, -linf);
	dp[0] = 0;

	for(auto [x, y] : a)
		for(int i = l - y; i >= 0; --i)
			dp[i + y] = max(dp[i + y], dp[i] + col[x]);
	
	for(int i = 1; i <= l; ++i) dp[i] = max(dp[i], dp[i - 1]);

	cout << dp[l] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


