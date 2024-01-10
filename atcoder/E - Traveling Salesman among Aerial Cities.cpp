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

const i64 linf = 1e16L;

i64 dp[1 << 17][17];

void solve() {
	
	int n;

	cin >> n;

	vector<tuple<int, int, int>> p(n);

	for(auto& [x, y, z] : p) cin >> x >> y >> z;

	for(int i = 0; i < (1 << n); ++i)
	for(int j = 0; j < n; ++j)
		dp[i][j] = linf;

	dp[1][0] = 0;

	for(int i = 1; i < (1 << n); ++i) {
		for(int X = i; X; X -= X & -X) {
			int k = __builtin_ctz(X);
			auto [x0, y0, z0] = p[k];
			for(int j = 0; j < n; ++j) {
				auto [x1, y1, z1] = p[j];
				i64 c = dp[i][k] + abs(x1 - x0) + abs(y1 - y0) + max(0, z1 - z0);
				dp[i | (1 << j)][j] = min(dp[i | (1 << j)][j], c);
			}
		}
	}

	cout << dp[(1 << n) - 1][0] << '\n';	
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
