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

vector<int> a;
int n;
i64 m;

i64 count(i64 x) {
	i64 cnt = 0;
	int hi = n - 1;
	for(int i = 0; i < n; ++i) {
		while(hi > 0 && a[i] + a[hi - 1] >= x) --hi;
		if(a[i] + a[hi] >= x) cnt += n - hi;
	}
	return cnt;
}

void solve() {

	cin >> n >> m;
	
	a.resize(n);
	
	for(int& v : a) cin >> v;
	
	sort(a.begin(), a.end());
	
	vector<i64> pre(n + 1, 0);
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i - 1];
	
	int x = 0, hi = n - 1;
	i64 cnt = 0, ans = 0;
	
	for(int k = 18; k >= 0; --k) if(count(x + (1 << k)) >= m) x += 1 << k;
	
	for(int i = 0; i < n; ++i) {
		while(hi > 0 && a[hi - 1] + a[i] > x) --hi;
		if(a[i] + a[hi] > x) {
			ans += a[i] * (n - hi + 0LL) + pre[n] - pre[hi];
			cnt += n - hi;
		}
	}

	ans += max(0LL, m - cnt) * x;
	
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

