#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 410; 

int tc, a[MAXN];

i64 dp[MAXN][MAXN];

int f(int from, int to, int D) {
	return min((from - to + D) % D, (to - from + D) % D);
}

i64 DP(int l, int r, int target, int D) {
	if(dp[l][r] != -1) return dp[l][r];
	int lo = l, hi = r;
	while(lo <= r && a[lo] == target) ++lo;
	while(hi >= l && a[hi] == target) --hi;
	if(lo > hi) return dp[l][r] = 0;
	return min(DP(lo, hi, a[lo], D) + f(a[lo], target, D), DP(lo, hi, a[hi], D) + f(a[hi], target, D));
}

void solve() {
	int n, d;
	cin >> n >> d;
	for(int i = 0; i < n; ++i) cin >> a[i];

	for(int i = 0; i < n; ++i)
	for(int j = i; j < n; ++j)
		dp[i][j] = -1;

	cout << "Case #" << ++tc << ": " << DP(0, n - 1, 0, d) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}