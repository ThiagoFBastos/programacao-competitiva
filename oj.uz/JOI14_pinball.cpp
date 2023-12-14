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
 
const i64 INF = 1e15L;
 
int n, m;
 
vector<i64> st;
 
i64 query(int l, int r) {
	i64 ans = INF;
	for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if(l & 1) ans = min(ans, st[l++]);
		if(~r & 1) ans = min(ans, st[r--]);
	}
	return ans;
}
 
void upd(int k, i64 x) {
	k += n;
	st[k] = min(st[k], x);
	for(k >>= 1; k; k >>= 1) st[k] = min(st[k << 1], st[(k << 1) | 1]);
}
 
void solve() {
	
	cin >> n >> m;
 
	vector<int> a(n), b(n), c(n), d(n);
	vector<i64> dp(n, 0);
	i64 ans = INF;
 
	for(int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i] >> d[i];
	
	auto x = c;
	sort(x.begin(), x.end());
 
	st.assign(2 * n + 1, INF);
	
	for(int i = 0; i < n; ++i) {
		if(a[i] == 1) {
			int k = lower_bound(x.begin(), x.end(), c[i]) - x.begin();
			upd(k, d[i]);
			dp[i] = d[i];
		} else {
			int l = lower_bound(x.begin(), x.end(), a[i]) - x.begin();
			int r = upper_bound(x.begin(), x.end(), b[i]) - x.begin() - 1;
			dp[i] = d[i] + query(l, r);
			upd(lower_bound(x.begin(), x.end(), c[i]) - x.begin(), dp[i]);
		}
		if(b[i] == m) ans = min(ans, dp[i]);
	}
 
	fill(st.begin(), st.end(), INF);
 
	for(int i = 0; i < n; ++i) {
		if(b[i] == m) {
			int k = lower_bound(x.begin(), x.end(), c[i]) - x.begin();
			upd(k, d[i]);
			dp[i] += d[i];
		} else {
			int l = lower_bound(x.begin(), x.end(), a[i]) - x.begin();
			int r = upper_bound(x.begin(), x.end(), b[i]) - x.begin() - 1;
			i64 q = query(l, r);
			dp[i] += q;
			upd(lower_bound(x.begin(), x.end(), c[i]) - x.begin(), d[i] + q);
		}
		ans = min(ans, dp[i]);
	}
 
	if(ans >= INF) ans = -1;
 
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
