#pragma GCC optimize("O3")
#pragma GCC target("popcnt", "mmx", "sse", "sse2", "sse3", "sse4")

#include "bits/stdc++.h"
using namespace std;

using ll = long long;

const ll inf = 1e16L;
const int N = 5e3 + 1;

int sp[13][N];

void create(vector<int>& a) {
	int n = a.size();
	int m = 32 - __builtin_clz(n);
	
	for(int i = 0; i < n; ++i) sp[0][i] = a[i];
	
	for(int i = 1; i < m; ++i)
	for(int j = 0; j + (1 << i) - 1 < n; ++j)	
		sp[i][j] = sp[i - 1][j] | sp[i - 1][j + (1 << (i - 1))];
}

int query(int l, int r) {
	int t = 31 - __builtin_clz(r - l + 1);
	return sp[t][l] | sp[t][r - (1 << t) + 1];
}

ll dp[N][N];

void decomp(int k, int l, int r, int lo, int hi) {
	if(l > r) return;
		
	int mid = (l + r) >> 1;
		
	auto ans = make_pair(-inf, lo);
		
	for(int i = lo; i <= min(hi, mid - 1); ++i) ans = max(ans, make_pair(dp[k - 1][i] + query(i + 1, mid), i));
		
	dp[k][mid] = ans.first;
		
	decomp(k, l, mid - 1, lo, ans.second);
	decomp(k, mid + 1, r, ans.second, hi);
}

void solve() {
	int n, k;
	cin >> n >> k;
	
	vector<int> a(n + 1, 0);
		
	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	create(a);
	
	fill(dp[0], dp[0] + n + 1, -inf);
	
	dp[0][0] = 0;
	
	for(int i = 1; i <= k; ++i) decomp(i, i, n, i - 1, n);
	
	cout << dp[k][n] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}