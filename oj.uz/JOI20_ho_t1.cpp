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
 
	vector<ii> a(n + 1);
	vector<int> b(n), ans(n + 1), suf(n + 1);
 
	for(int i = 0; i <= n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}
 
	for(int& v : b) cin >> v;
 
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
 
	suf.back() = 0;
 
	for(int i = n - 1; i >= 0; --i) suf[i] = max(suf[i + 1], max(0, a[i + 1].first - b[i]));
 
	int pre = 0;
 
	for(int i = 0; i <= n; ++i) {
		ans[a[i].second] = max(pre, suf[i]);
		if(i < n) pre = max(pre, max(0, a[i].first - b[i]));
	}
 
	for(int v : ans) cout << v << ' ';
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
