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

	vector<int> h(n), w(m);

	for(int& v : h) cin >> v;
	for(int& v : w) cin >> v;

	sort(h.begin(), h.end());
	sort(w.begin(), w.end());

	vector<i64> pre(n, 0), suf(n, 0);

	for(int i = 1; i < n; ++i) {
		pre[i] = pre[i - 1];
		if(i % 2) pre[i] += h[i] - h[i - 1];
	}

	for(int i = n - 2; i >= 0; --i) {
		suf[i] = suf[i + 1];
		if((n - i) % 2 == 0) suf[i] += h[i + 1] - h[i];
	}

	i64 ans = LLONG_MAX;

	for(int i = 0; i < n; ++i) {
		if(i % 2) continue;
		auto k = lower_bound(w.begin(), w.end(), h[i]);
		int x = INT_MAX;
		if(k != w.end()) x = *k - h[i];
		if(k != w.begin()) x = min(x, h[i] - *prev(k));
		ans = min(ans, pre[i] + suf[i] + x);
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
