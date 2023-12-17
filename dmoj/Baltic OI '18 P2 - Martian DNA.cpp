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
	int n, k, r;
	
	cin >> n >> k >> r;
	
	vector<int> a(n), cnt(k, 0), use(k, 0);
	
	for(int& v : a) cin >> v;
	
	for(int i = 0; i < r; ++i) {
		int p;
		cin >> p;
		cin >> cnt[p];
	}
	
	int fails = 0, ans = n + 1;
	
	for(int i = 0; i < k; ++i) fails += !!cnt[i];
	
	for(int i = 0, hi = 0; i < n; ++i) {
		while(hi < n && fails) {
			if(++use[a[hi]] == cnt[a[hi]]) --fails;
			++hi;
		}
		if(fails == 0) ans = min(ans, hi - i);
		if(use[a[i]]-- == cnt[a[i]]) ++fails;
	}
	
	if(ans > n) {
		cout << "impossible\n";
		return;
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
