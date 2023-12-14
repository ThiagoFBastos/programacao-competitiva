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
 
void solve() {				
	int n;
	cin >> n;
	
	vector<pair<i64, i64>> a(n);
	vector<i64> pre(n + 1);
	i64 ans, suf;
	
	for(auto& [x, y] : a) cin >> x >> y;
	
	sort(a.begin(), a.end());
	
	pre[0] = 0;
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i - 1].second;
		
	ans = suf = LLONG_MIN;
	
	for(int i = n - 1; i >= 0; --i) {
		suf = max(suf, pre[i + 1] - a[i].first);
		ans = max(ans, suf - pre[i] + a[i].first);
	}
	
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
