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
 
struct SegTree {
	vector<int> st, lazy;
	int n;
	
	SegTree() {}
	
	SegTree(int n) {
		this->n = n;
		int K = 1 << (33 - __builtin_clz(n));
		st.assign(K, 0);
		lazy.assign(K, 0);
	}
	
	void push(int no) {
		if(!lazy[no]) return;
		int l = 2 * no, r = 2 * no + 1;
		st[l] += lazy[no];
		st[r] += lazy[no];
		lazy[l] += lazy[no];
		lazy[r] += lazy[no];
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
			upd(x, max(mid + 1, l), r, mid + 1, hi, 2 * no + 1);
			st[no] = min(st[2 * no], st[2 * no + 1]);
		}
	}
	
	int query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return inf;
		else if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) / 2;
		push(no);
		int L = query(l, min(r, mid), lo, mid, 2 * no);
		int R = query(max(mid + 1, l), r, mid + 1, hi, 2 * no + 1);
		return min(L, R);
	}
	
	void upd(int x, int l, int r) {
		upd(x, l, r, 0, n - 1);
	}
	
	int query(int l, int r) {
		return query(l, r, 0, n - 1);
	}
};
 
void solve() {
	
	int n;
	
	cin >> n;
	
	vector<int> cnt(2, 0);
	SegTree X[2];
	
	for(int i = 0; i < 2; ++i) X[i] = SegTree(n);
	
	for(int i = 1; i <= n; ++i) {
		int v, t, pts[2] = {0};
		
		cin >> v >> t;
		
		--t, --v;
		++cnt[t];
		
		X[t].upd(-1, 0, v);
		X[t ^ 1].upd(1, 0, v);
		
		for(int i = 0; i < 2; ++i) {
			pts[i] += cnt[i] > cnt[i ^ 1];
			pts[i] += X[i].query(0, n - 1) < 0;
			pts[i] = !!pts[i];
		}
	
		if(pts[0] == pts[1]) cout << "?\n";
		else if(pts[0]) cout << ">\n";
		else cout << "<\n";
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
