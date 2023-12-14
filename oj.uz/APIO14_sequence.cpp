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
 
const int N = 1e5 + 1, K = 202;
const i64 inf = 1e18L;
 
i64 dp[2][N];
int n, k, pa[K][N], pre[N];
 
void rec(int k, int l, int r, int lo, int hi) {
	
	int mid = (l + r) / 2;
	auto ans = make_pair(-inf, 0);
	int m = min(mid - 1, hi);
	
	for(int i = lo; i <= m; ++i) {
		i64 s = pre[mid] - pre[i];
		ans = max(ans, make_pair(dp[0][i] + (pre[n] - s) * s, i));
	}
	
	dp[1][mid] = ans.first;
	pa[k][mid] = ans.second;
	
	if(l < mid) rec(k, l, mid - 1, lo, ans.second);
	if(r > mid) rec(k, mid + 1, r, ans.second, hi);
}
 
void solve() {
 
	cin >> n >> k;
	
	++k;
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
	}
	
	for(int i = 1; i <= n; ++i) dp[0][i] = (pre[n] - pre[i] + 0LL) * pre[i];
	
	for(int i = 2; i <= k; ++i) {
		rec(i, i, n, i - 1, n);
		for(int j = 0; j <= n; ++j) dp[0][j] = dp[1][j];
	}
	
	cout << dp[0][n] / 2 << '\n';
	
	vector<int> s;
	
	for(int i = n; k > 1; --k) {
		s.emplace_back(pa[k][i]);
		i = pa[k][i];
	}
 
	for(int i = (int)s.size() - 1; i >= 0; --i) cout << s[i] << ' ';
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
