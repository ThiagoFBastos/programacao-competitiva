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

int n, m;
vector<ii> a, b;

i64 rec(int l, int r, int lo, int hi) {
	
	if(l > r) return 0;
	
	int mid = (l + r) / 2;
	auto ans = make_pair(0LL, -1);
	
	for(int k = lo; k <= hi; ++k) {
		int x = b[k].first - a[mid].first;
		int y = b[k].second - a[mid].second;
		ans = max(ans, make_pair(1LL * max(0, x) * y, k));
	}
	
	return max(ans.first, max(rec(l, mid - 1, lo, ans.second), rec(mid + 1, r, ans.second, hi)));
}

void solve() {

	cin >> n >> m;
	
	a.resize(n);
	b.resize(m);
	
	int v = INT_MAX, k = 0;
	
	for(auto& [x, y] : a) cin >> x >> y;
	for(auto& [x, y] : b) cin >> x >> y;
	
	sort(a.begin(), a.end());
	sort(b.rbegin(), b.rend());
					 	
	for(int i = 0; i < n; ++i) {
		if(v > a[i].second) {
			a[k++] = a[i];
			v = a[i].second;
		}
	}
	
	a.resize(k);
	
	v = INT_MIN;
	k = 0;

	for(int i = 0; i < m; ++i) {
		if(v < b[i].second) {
			b[k++] = b[i];
			v = b[i].second;
		}
	}
	
	b.resize(k);
	reverse(b.begin(), b.end());
	
	n = a.size();
	m = b.size();
	
	cout << max(0LL, rec(0, n - 1, 0, m - 1)) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}