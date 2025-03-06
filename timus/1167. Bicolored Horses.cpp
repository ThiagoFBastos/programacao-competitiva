#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 512, INF = 1e9;

array<int, N> dp[2];
int cnt[N];

int C(int l, int r) {
	int _1 = cnt[r] - cnt[l - 1];
	return (r - l + 1 - _1) * _1;
}

void rec(int l, int r, int lo, int hi) {
	if(lo > hi) return;

	int mid = (lo + hi) / 2;	

	auto cost = make_pair(INF, l);	

	for(int k = l; k <= min(r, mid - 1); ++k)
		cost = min(cost, make_pair(C(k + 1, mid) + dp[0][k], k));

	dp[1][mid] = cost.first;

	rec(l, cost.second, lo, mid - 1);
	rec(cost.second, r, mid + 1, hi);
}

void solve() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) {
		cin >> cnt[i];
		cnt[i] += cnt[i - 1];
	}
	fill(dp[0].begin(), dp[0].end(), INF);
	dp[0][0] = 0;
	for(int i = 1; i <= k; ++i) {
		rec(i - 1, n, i, n);
		swap(dp[0], dp[1]);
	}
	cout << dp[0][n] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}