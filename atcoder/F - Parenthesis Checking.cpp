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

const int inf = 1e9;

int n, q;
string s;

struct segtree {
	vector<int> st, lazy;
	int n;
	segtree(vector<int>& a) {
		n = a.size();
		int m = 1 << (33 - __builtin_clz(n));
		st.resize(m);
		lazy.resize(m);
		create(a, 0, n - 1);
	}
	
	void create(vector<int>& a, int lo, int hi, int no = 1) {
		lazy[no] = 0;
		if(lo == hi) st[no] = a[lo];
		else {
			int mid = (lo + hi) / 2;
			create(a, lo, mid, 2 * no);
			create(a, mid + 1, hi, 2 * no + 1);
			st[no] = min(st[2 * no], st[2 * no + 1]);
		}
	}
	
	void push(int no) {
		if(!lazy[no]) return;
		int l = 2 * no, r = 2 * no + 1;
		lazy[l] += lazy[no];
		lazy[r] += lazy[no];
		st[l] += lazy[no];
		st[r] += lazy[no];
		lazy[no] = 0;
	}
	
	void upd(int x, int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return;
		else if(r - l == hi - lo) {
			st[no] += x;
			lazy[no] += x;
		} else {
			int mid = (lo + hi) / 2;
			push(no);
			upd(x, l, min(r, mid), lo, mid, 2 * no);
			upd(x, max(l, mid + 1), r, mid + 1, hi, 2 * no + 1);
			st[no] = min(st[2 * no], st[2 * no + 1]);
		}
	}
	
	int query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return inf;
		else if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) / 2;
		push(no);
		int L = query(l, min(r, mid), lo, mid, 2 * no);
		int R = query(max(l, mid + 1), r, mid + 1, hi, 2 * no + 1);
		return min(L, R);
	}
	
	void upd(int x, int l, int r) {
		upd(x, l, r, 0, n - 1);
	}
	
	int query(int l, int r) {
		return query(l, r, 0, n - 1);
	}
};

int val(char ch) {
	return ch == '(' ? 1 : -1;
}

void solve() {
	cin >> n >> q >> s;
	
	vector<int> pre(n + 1, 0);
	
	for(int i = 1; i <= n; ++i)
		pre[i] = pre[i - 1] + val(s[i - 1]);
	
	segtree st(pre);
	
	while(q--) {
		int t, l, r;
		cin >> t >> l >> r;
		if(t == 1) {
			int a = val(s[l - 1]), b = val(s[r - 1]);
			st.upd(-a + b, l, n);
			st.upd(-b + a, r, n);
			swap(s[l - 1], s[r - 1]);
		} else {
			int i = st.query(l - 1, l - 1);
			int k = st.query(l, r) - i;
			int j = st.query(r, r) - i;
			cout << (k < 0 || j ? "No\n" : "Yes\n");
		}
	}	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}
