#include "bits/stdc++.h"
 
using namespace std;
template<class T>
struct BIT {
	vector<T> bit;
	
	BIT() {}
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

template<class T>
struct BITRange {
	BIT<T> X, Y;
	
	BITRange(int n) {
		X = BIT<T>(n);
		Y = BIT<T>(n);
	}
	
	void upd(int l, int r, T x) {
		X.upd(l, (l - 1) * x);
		X.upd(r + 1, -r * x);
		Y.upd(l, x);
		Y.upd(r + 1, -x);
	}
	
	T prefix(int k) {
		return k * Y.query(k) - X.query(k);
	}
	
	T query(int l, int r) {
		return prefix(r) - prefix(l - 1);
	}
};

using ll = long long;

void solve() {
	int n, q;
	
	cin >> n >> q;
	
	BITRange<ll> bit(n);
	
	while(q--) {
		int type, l, r, v;
		cin >> type >> l >> r;
		--l, --r;
		if(type == 0) {
			cin >> v;
			bit.upd(l, r, v);
		} else cout << bit.query(l, r) << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}