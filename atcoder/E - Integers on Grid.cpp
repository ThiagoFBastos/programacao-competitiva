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

using T = tuple<int, int, int, int>;

void solve() {
	int h, w, n;
	
	cin >> h >> w >> n;
	
	vector<T> a(n);
	vector<int> rows(h + 1, 0), cols(w + 1, 0), ans(n); 
	
	for(int i = 0; i < n; ++i) {
		int x, y, v;
		cin >> x >> y >> v;
		a[i] = {v, x, y, i};
	}
	
	sort(a.rbegin(), a.rend());
	
	for(int k = 0; k < n; ) {
		int j = k;
		while(j < n && get<0>(a[j]) == get<0>(a[k])) {
			auto [v, x, y, i] = a[j];
			ans[i] = max(rows[x], cols[y]);
			++j;
		}
		while(k < j) {
			auto [v, x, y, i] = a[k];
			rows[x] = max(rows[x], 1 + ans[i]);
			cols[y] = max(cols[y], 1 + ans[i]);
			++k;
		}
	}
	
	for(int v : ans) cout << v << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

