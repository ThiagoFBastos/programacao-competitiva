#include "bits/stdc++.h"
using namespace std;
vector<int> bit;
int n, q;
void upd(int k, int x) {
	if(k < 0) return;
	for(k = n - k; k <= n; k += k & -k) bit[k] += x;
}
int query(int k) {
	int ans = 0;
	if(k < 0) return 0;
	for(k = n - k; k > 0; k -= k & -k) ans += bit[k];
	return ans;
}
void solve() {
	cin >> n >> q;
	vector<int> a(n), ans(q);
	vector<vector<int>> g(n + 1);
	vector<vector<pair<int, int>>> b(n + 1), c(n);
	bit.assign(n + 1, 0);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		if(a[i] <= n) g[a[i]].push_back(i);
	}
	for(int i = 0; i < q; ++i) {
		int L, R;
		cin >> L >> R;
		c[R - 1].push_back({L - 1, i});
	}
	for(int i = 0; i < n; ++i) {
		int x = a[i], l, r;
		if(x <= n) {
			int k = lower_bound(g[x].begin(), g[x].end(), i) - g[x].begin();
			if(1 + k >= x) {
				l = k == x - 1 ? 0 : g[x][k - x] + 1;
				r = g[x][k - x + 1];
				upd(r, 1);
				upd(l - 1, -1);
				b[k + 1 == size(g[x]) ? n : g[x][k + 1]].push_back({l, r});
			}
		}
		for(auto [l, r] : b[i]) {
			upd(r, -1);
			upd(l - 1, 1);
		}
		for(auto [L, pos] : c[i]) ans[pos] = query(L);
	}
	for(int x : ans) cout << x << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}