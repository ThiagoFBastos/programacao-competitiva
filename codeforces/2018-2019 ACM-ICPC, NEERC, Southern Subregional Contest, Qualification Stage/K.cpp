#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

const int N = 5e3 + 10, INF = 1e9;

int bit[N];

void upd(int k, int x) {
	for(++k; k < N; k += k & -k) bit[k] += x;
}

int find_by_order(int k) {
	int i = 0;
	for(int j = 31 - __builtin_clz(N); j >= 0; --j) {
		int _i = i | (1 << j);
		if(_i >= N || k - bit[_i] <= 0) continue;
		i = _i;
		k -= bit[_i];
	}
	return i;
}

void solve() {
	
	int n, m;

	cin >> n >> m;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	vector<int> dp(n + 1, -INF);

	dp[0] = 0;

	for(int i = 1; i <= n; ++i) {
		memset(bit, 0, sizeof bit);
		for(int j = i; j; --j) {
			int l = i - j + 1;
			upd(a[j - 1], 1);
			int median = 2 * find_by_order((l + 1) / 2);
			if(median >= 2 * m) dp[i] = max(dp[i], dp[j - 1] + 1);
		}
	}

	cout << max(0, dp[n]) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

