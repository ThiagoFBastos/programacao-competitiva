#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 410; 

int tc, a[MAXN];

i64 dp[MAXN][MAXN][2];

int f(int from, int to, int D) {
	return min((from - to + D) % D, (to - from + D) % D);
}

i64 DP(int l, int r, int t, int D) {
	if(dp[l][r][t] != -1) return dp[l][r][t];
	int lo = l, hi = r, target = t ? a[r] : a[l];
	while(lo <= r && a[lo] == target) ++lo;
	while(hi >= l && a[hi] == target) --hi;
	if(lo > hi) return dp[l][r][t] = 0;
	return dp[l][r][t] = min(DP(lo, hi, 0, D) + f(a[lo], target, D), DP(lo, hi, 1, D) + f(a[hi], target, D));
}

void solve() {
	int n, d;
	cin >> n >> d;

	int lo = n, hi = 0;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		if(!a[i]) continue;
		lo = min(lo, i);
		hi = i;
	}

	cout << "Case #" << ++tc << ": " ;

	if(lo > hi) {
		cout << "0\n";
		return;
	}

	for(int i = 0; i < n; ++i)
	for(int j = i; j < n; ++j)
	for(int k = 0; k < 2; ++k)
		dp[i][j][k] = -1;

	cout << min(DP(lo, hi, 0, d) + f(a[lo], 0, d), DP(lo, hi, 1, d) + f(a[hi], 0, d)) << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}