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

const i64 linf = 1e18L;

void solve() {
	int n;
	i64 x, y;

	cin >> n >> x >> y;

	vector<int> a(n), b(n);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	vector<i64> dp(1 << n, linf);

	dp.back() = 0;
	for(int i = (1 << n) - 1; i; --i) {
		int k = n - __builtin_popcount(i);
		int S = i ^ ((1 << n) - 1);
		for(int K = i; K; K -= K & -K) {
			int j = __builtin_ctz(K);
			int bits = __builtin_popcount(S & ~((1 << j) - 1));
			dp[i ^ (1 << j)] = min(dp[i ^ (1 << j)], dp[i] + x * abs(b[j] - a[k]) + y * bits);
		}
	}

	cout << dp[0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
