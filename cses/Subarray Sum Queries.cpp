#include "bits/stdc++.h"
 
using namespace std;
 
vector<int> a;
int n, q;
 
struct info {
	long long pre, suf, sum, max;
	info() {pre = suf = sum = max = 0;}
	info(long long x) {
		pre = suf = max = (x < 0) ? 0 : x;
		sum = x;
	}
};
 
struct segtree {
	vector<info> st;
	void combine(info& src1, info& src2, info& dest) {
		dest.pre = max(src1.pre, src1.sum + src2.pre);
		dest.suf = max(src2.suf, src2.sum + src1.suf);
		dest.sum = src1.sum + src2.sum;
		dest.max = max(max(src1.suf + src2.pre, max(src1.max, src2.max)), max(dest.pre, dest.suf)); 
	}
	void init(int lo, int hi, int no = 1) {
		if(lo == hi) st[no] = info(a[lo]);
		else {
			int mid = (lo + hi) >> 1;
			init(lo, mid, no << 1);
			init(mid + 1, hi, (no << 1) | 1);
			combine(st[no << 1], st[(no << 1) | 1], st[no]);
		}
	}
	segtree() {
		st.resize(1 << (33 - __builtin_clz(n)));
		init(0, n - 1);
	}
	info query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return info();
		else if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) >> 1;
		info L = query(l, min(r, mid), lo, mid, no << 1), R = query(max(l, mid + 1), r, mid + 1, hi, (no << 1) | 1), S;
		combine(L, R, S);
		return S;
	}
	long long query() {
		return st[1].max;
	}
	void upd(int k, long long x, int lo, int hi, int no = 1) {
		if(lo == hi) st[no] = info(x);
		else {
			int mid = (lo + hi) >> 1;
			k <= mid ? upd(k, x, lo, mid, no << 1) : upd(k, x, mid + 1, hi, (no << 1) | 1);
			combine(st[no << 1], st[(no << 1) | 1], st[no]);
		}
	}
	void upd(int k, long long x) {
		upd(k, x, 0, n - 1);
	}
};
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	a.resize(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	segtree st;
	while(q--) {
		int k, x;
		cin >> k >> x;
		st.upd(k - 1, x);
		cout << st.query() << '\n';
	}	
	return 0;
}
