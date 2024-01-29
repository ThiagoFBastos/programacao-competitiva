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

struct node {
	i64 cnt = 0;
	i64 pre[2] = {0};
	i64 suf[2] = {0};
	int n;
};

void merge(node& a, node& b, node& c) {
	a.cnt = b.cnt + c.cnt;
	a.n = b.n + c.n;
	for(int i = 0; i < 2; ++i) {
		a.cnt += b.suf[i] * c.pre[i ^ 1];
		a.pre[i] = b.pre[i];
		a.suf[i] = c.suf[i];
		if(b.pre[i] == b.n) a.pre[i] += c.pre[i ^ (b.n & 1)];
		if(c.suf[i] == c.n) a.suf[i] += b.suf[i ^ (c.n & 1)];
	}
}

vector<int> lazy, a;
vector<node> st;
int n, q;

void create(int lo, int hi, int no = 1) {
	lazy[no] = 0;
	if(lo == hi) {
		st[no].cnt = 1;
		st[no].pre[a[lo]] = st[no].suf[a[lo]] = 1;
		st[no].n = 1;
	} else {
		int mid = (lo + hi) / 2;
		create(lo, mid, 2 * no);
		create(mid + 1, hi, 2 * no + 1);
		merge(st[no], st[2 * no], st[2 * no + 1]);
	}
}

void push(int no) {
	if(!lazy[no]) return;
	int l = 2 * no, r = 2 * no + 1;
	lazy[l] ^= 1;
	lazy[r] ^= 1;
	lazy[no] = 0;
	for(int k : {l, r}) {
		swap(st[k].pre[0], st[k].pre[1]);
		swap(st[k].suf[0], st[k].suf[1]);
	}
}

void upd(int l, int r, int lo, int hi, int no = 1) {
	if(l > r) return;
	else if(r - l == hi - lo) {
		lazy[no] ^= 1;
		swap(st[no].pre[0], st[no].pre[1]);
		swap(st[no].suf[0], st[no].suf[1]);
	} else {
		int mid = (lo + hi) / 2;
		push(no);
		upd(l, min(r, mid), lo, mid, 2 * no);
		upd(max(mid + 1, l), r, mid + 1, hi, 2 * no + 1);
		merge(st[no], st[2 * no], st[2 * no + 1]);
	}
}

node query(int l, int r, int lo, int hi, int no = 1) {
	if(l > r) return node();
	else if(r - l == hi - lo) return st[no];
	int mid = (lo + hi) / 2;
	push(no);
	node L = query(l, min(r, mid), lo, mid, 2 * no);
	node R = query(max(mid + 1, l), r, mid + 1, hi, 2 * no + 1);
	node Z;
	merge(Z, L, R);
	return Z;
}

void solve() {
	cin >> n >> q;
	a.resize(n);
	for(int& v : a) cin >> v;
	int lg = 31 - __builtin_clz(n);
	st.resize(4 << lg);
	lazy.resize(4 << lg);
	create(0, n - 1);
	while(q--) {
		int t, l, r;
		cin >> t >> l >> r;
		--l, --r;
		if(t == 1) upd(l, r, 0, n - 1);
		else cout << query(l, r, 0, n - 1).cnt << '\n';
	}	
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}

