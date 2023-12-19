#include "bits/stdc++.h"
using namespace std;
const int inf = 2e9;
struct segtree {
	vector<int> st;
	int n, dx;
	segtree(vector<int>& a, int dx) {
		this->dx = dx;
		n = 1 << (32 - __builtin_clz(a.size()));
		st.resize(2 * n);
		for(int i = n; i < 2 * n; ++i) st[i] = (i - n < int(a.size()) ? a[i - n] : inf) + (i - n) * dx;
		for(int i = n - 1; i; --i) st[i] = min(st[i << 1], st[i << 1 | 1]);
	}
	void upd(int k, int x) {
		k += n;
		st[k] = x + dx * (k - n);
		for(k >>= 1; k; k >>= 1) st[k] = min(st[k << 1], st[k << 1 | 1]);
	}
	int query(int l, int r) {
		int ans = inf;
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) ans = min(ans, st[l++]);
			if(~r & 1) ans = min(ans, st[r--]);
		}
		return ans;
	}
};
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int& x : a) cin >> x;
	segtree X(a, 1), Y(a, -1);
	while(q--) {
		int t, i, j;
		cin >> t >> i;
		if(t == 1) {
			cin >> j;
			X.upd(i - 1, j);
			Y.upd(i - 1, j);
			a[i - 1] = j;
		} else cout << min(i - 1 + Y.query(0, i - 1), X.query(i, n - 1) - i + 1) << '\n';
	}
	return 0;
}
