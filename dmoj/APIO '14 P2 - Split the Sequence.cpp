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

const i64 inf = 2e18L;
const int N = 1e5 + 1, K = 201;

int n, k;

i64 dp[2][N], pre[N];
int pos[K][N];

void rec(int k, int l, int r, int lo, int hi) {
	if(l > r) return;
	
	int mid = (l + r) >> 1;
	auto best = make_pair(-inf, 0);
	
	int last = min(hi, mid - 1);
	
	for(int i = lo; i <= last; ++i) {
		i64 cost = dp[~k & 1][i] + pre[i] * (pre[mid] - pre[i]);
		best = max(best, make_pair(cost, -i));
	}
	
	dp[k & 1][mid] = best.first;
	pos[k][mid] = -best.second;
	
	rec(k, l, mid - 1, lo, -best.second);
	rec(k, mid + 1, r, -best.second, hi);
}

void solve() {
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
	}
	
	fill(dp[0], dp[0] + n + 1, -inf);
	
	dp[0][0] = 0;
	++k;
	
	for(int i = 1; i <= k; ++i) rec(i, i, n, i - 1, n);
	
	cout << dp[k & 1][n] << '\n';
	
	for(int i = pos[k][n]; i > 0; --k, i = pos[k][i]) cout << i << ' ';
	
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
