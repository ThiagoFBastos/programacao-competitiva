#include "bits/stdc++.h"
 
using namespace std;

template<class T>
using ii = pair<T, int>;

template<class T>
struct LazyPropagation {
	vector<ii<T>> st; 
	vector<T> lazy;
	vector<bool> marked;
	int n;
	
	void create(vector<T>& a, int lo, int hi, int no = 1) {
		lazy[no] = 0;
		marked[no] = false;
		if(lo == hi) st[no] = {a[lo], -lo - 1};
		else {
			int mid = (lo + hi) >> 1;
			create(a, lo, mid, no << 1);
			create(a, mid + 1, hi, (no << 1) | 1);
			st[no] = max(st[no << 1], st[(no << 1) | 1]);
		}
	}
	
	LazyPropagation(vector<T>& a) {
		n = a.size();
		int K = 1 << (33 - __builtin_clz(n));
		st.resize(K);
		lazy.resize(K);
		marked.resize(K);
		create(a, 0, n - 1);
	}
	
	void push(int no) {
		if(!marked[no]) return;
		int left = no << 1, right = (no << 1) | 1;
		st[left].first += lazy[no];
		st[right].first += lazy[no];
		lazy[left] += lazy[no];
		lazy[right] += lazy[no];
		marked[left] = marked[right] = true;
		lazy[no] = 0;
		marked[no] = false;
	}
	
	void upd(int l, int r, T v, int lo, int hi, int no = 1) {
		if(l > r) return;
		else if(r - l == hi - lo) {
			st[no].first += v;
			lazy[no] += v;
			marked[no] = true;
		} else {
			int mid = (lo + hi) >> 1;
			push(no);
			upd(l, min(r, mid), v, lo, mid, no << 1);
			upd(max(mid + 1, l), r, v, mid + 1, hi, (no << 1) | 1);
			st[no] = max(st[no << 1], st[(no << 1) | 1]);
		}
	}
	
	ii<T> query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return {-1, -1};
		else if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) >> 1;
		push(no);
		ii<T> L = query(l, min(r, mid), lo, mid, no << 1);
		ii<T> R = query(max(mid + 1, l), r, mid + 1, hi, (no << 1) | 1);
		return max(L, R);
	}
	
	void upd(int l, int r, T v) {
		upd(l, r, v, 0, n - 1);
	}
	
	ii<T> query(int l, int r) {
		return query(l, r, 0, n - 1);
	}
};

void solve() {
	int n, q;
	
	cin >> n >> q;
	
	if(cin.eof()) exit(0);
	
	vector<int> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];		
	
	LazyPropagation<int> lp(a);
	
	while(q--) {
		char type;
		int i, j, v;
		
		cin >> type >> i >> j;
		
		--i, --j;
		
		if(type == 'A') {
			cin >> v;
			lp.upd(i, j, v);
		} else cout << -lp.query(i, j).second << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}