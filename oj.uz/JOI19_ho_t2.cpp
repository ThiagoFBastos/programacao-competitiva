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
 
	int n, m;
	
	cin >> n >> m;
	
	vector<ii> a(n);
	vector<int> c(m), p(m, 0);
	
	for(auto& [y, x] : a) cin >> x >> y;
	for(int& x : c) cin >> x;
	
	sort(a.begin(), a.end());
	sort(c.begin(), c.end());
	
	for(int i = n - 1; i >= 0; --i) {
		int k = lower_bound(p.begin(), p.end(), a[i].first) - p.begin() - 1;
		if(k < 0 || c[k] < a[i].second) continue;
		p[k] = a[i].first;
	}
 
	int cur = m;
	while(cur > 0 && p[cur - 1] > 0) --cur;
	cout << m - cur << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
