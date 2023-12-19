#include "bits/stdc++.h"
using namespace std;
vector<long long> p;
vector<int> a;
int n, q;
struct segtree {
	vector<long long> st, lazy;	
	void build(int lo, int hi, int no = 1) {
		lazy[no] = 0;
		if(lo == hi) st[no] = p[lo];
		else {
			int mid = (lo + hi) >> 1;
			build(lo, mid, no << 1);
			build(mid + 1, hi, no << 1 | 1);
			st[no] = max(st[no << 1], st[no << 1 | 1]);
		}
	}
	segtree() {
		st.resize(1 << (33 - __builtin_clz(n + 1)));
		lazy.resize(st.size());
		build(0, n);
	}
	void push(int no) {
		if(!lazy[no]) return;
		int L = no << 1, R = no << 1 | 1;
		st[L] += lazy[no], st[R] += lazy[no], lazy[L] += lazy[no], lazy[R] += lazy[no], lazy[no] = 0;
	}
	void upd(int k, long long x, int lo, int hi, int no = 1) {
		if(hi < k) return;
		else if(lo >= k) st[no] += x, lazy[no] += x;
		else {
			int mid = (lo + hi) >> 1;
			push(no);
			upd(k, x, lo, mid, no << 1);
			upd(k, x, mid + 1, hi, no << 1 | 1);
			st[no] = max(st[no << 1], st[no << 1 | 1]);
		}
	}
	long long query(int L, int R, int lo, int hi, int no = 1) {
		if(L > R) return LLONG_MIN;
		else if(R - L == hi - lo) return st[no];
		int mid = (lo + hi) >> 1;
		push(no);
		return max(query(L, min(R, mid), lo, mid, no << 1), query(max(mid + 1, L), R, mid + 1, hi, no << 1 | 1));
	}
	void upd(int k, long long x) {
		upd(k, x, 0, n);
	}
	long long query(int L, int R) {
		return query(L, R, 0, n);
	}
};
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	p.resize(n + 1);
	a.resize(n);
	p[0] = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i - 1];
		p[i] = a[i - 1] + p[i - 1];
	}
	segtree st;
	while(q--) {
		int t, i, j;
		cin >> t >> i >> j;	
		if(t == 2) cout << max(0LL, st.query(i, j) - st.query(i - 1, i - 1)) << '\n';
		else {
			st.upd(i, j - a[i - 1]);
			a[i - 1] = j;
		}
	}
	return 0;
}
