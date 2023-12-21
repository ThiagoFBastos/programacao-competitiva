#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9 + 1;
struct BIT {
	vector<int> bit;
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	int query(int k) {
		int ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
	void upd(int k, int x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
};
void solve() {
	int n;
	cin >> n;
	vector<tuple<int, int, int>> L(n), R(n);
	vector<int> a(n, 0), b(n, 0);
	int k = 0, j = 0;
	for(int i = 0; i < n; ++i) {
		int l, r;
		cin >> l >> r;
		L[i] = {l, -r, i};
		R[i] = {r, -l, i};
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	BIT open(n), close(n);
	while(k < n) {
		auto [la, ra, ia] = L[k];
		auto [rb, lb, ib] = R[j];
		if(la <= rb) {
			int i = lower_bound(R.begin(), R.end(), make_tuple(-ra, -INF, 0)) - R.begin();
			a[ia] += open.query(i, n - 1);
			open.upd(i, 1);
			++k;
		} else {
			int i = lower_bound(L.begin(), L.end(), make_tuple(-lb, -INF, 0)) - L.begin();
			b[ib] += close.query(i, n - 1);
			close.upd(i, 1);
			open.upd(lower_bound(R.begin(), R.end(), make_tuple(rb, -INF, 0)) - R.begin(), -1);
			++j;
		}
	}
	for(; j < n; ++j) {
		auto [rb, lb, ib] = R[j];
		int i = lower_bound(L.begin(), L.end(), make_tuple(-lb, -INF, 0)) - L.begin();
		b[ib] += close.query(i, n - 1);
		close.upd(i, 1);
		open.upd(lower_bound(R.begin(), R.end(), make_tuple(rb, -INF, 0)) - R.begin(), -1);
	}
	for(int x : b) cout << x << ' ';
	cout << '\n';
	for(int x : a) cout << x << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
