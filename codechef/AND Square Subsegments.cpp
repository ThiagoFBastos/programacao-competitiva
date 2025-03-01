#include "bits/stdc++.h"

using namespace std;

struct SegTree {
	vector<long long> st, lazy;
	int n;
	
	SegTree(int n) {
		int m = 1 << (33 - __builtin_clz(n));
		this->n = n;
		st.assign(m, 0);
		lazy.assign(m, 0);
	}
	
	void push(int no, int sz) {
		if(!lazy[no]) return;
		int L = 2 * no, R = 2 * no + 1;
		st[L] += (sz + 1) / 2 * lazy[no], st[R] += sz / 2 * lazy[no];
		lazy[L] += lazy[no], lazy[R] += lazy[no];
		lazy[no] = 0;
	}
	
	void upd(int L, int R, int x, int lo, int hi, int no = 1) {
		if(L > R) return;
		else if(R - L == hi - lo) st[no] += (hi - lo + 1) * x, lazy[no] += x;	
		else {
			int mid = (lo + hi) / 2;
			push(no, hi - lo + 1);
			upd(L, min(R, mid), x, lo, mid, 2 * no);
			upd(max(L, mid + 1), R, x, mid + 1, hi, 2 * no + 1);
			st[no] = st[2 * no] + st[2 * no + 1];
		}
	}
	
	auto query(int L, int R, int lo, int hi, int no = 1) {
		if(L > R) return 0LL;
		else if(R - L == hi - lo) return st[no];
		int mid = (lo + hi) / 2;
		push(no, hi - lo + 1);
		return query(L, min(R, mid), lo, mid, 2 * no) + query(max(L, mid + 1), R, mid + 1, hi, 2 * no + 1);
	}
	
	void upd(int L, int R, int X) {
		upd(L, R, X, 0, n - 1);
	}
	
	auto query(int L, int R) {
		return query(L, R, 0, n - 1);
	}
};

void solve() {

	int n, q;
	
	cin >> n >> q;
	
	vector<array<int, 30>> bit_pos(n + 1);
	vector<vector<pair<int, int>>> a(n + 1);
	vector<int> v(n + 1);
	
	v[0] = 0;
	bit_pos[0].fill(0);
	
	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
	
		for(int j = 0; j < 30; ++j) {
			bit_pos[i][j] = bit_pos[i - 1][j];
			if(!(v[i] & 1 << j)) bit_pos[i][j] = i;
		}
		
		for(int k = i, u = v[i]; k; ) {
			auto p = make_pair(0, 0);
			for(int j = 0; (1 << j) <= u; ++j) if(u & 1 << j) p = max(p, make_pair(bit_pos[k][j], j));
			a[i].push_back({u, p.first + 1});
			k = p.first;
			u &= v[k];
		}
	}
	
	vector<vector<pair<int, int>>> Q(n + 1);
	vector<long long> cnt(q);
	SegTree st(n + 1);
	
	for(int i = 1; i <= n; ++i) {
		int last = i;
		for(auto& y : a[i]) {
			int mask = y.first, L = y.second;
			int x = sqrt(mask);
			if(x * x == mask) st.upd(L, last, 1);			
			last = L - 1;
		}
	}
	
	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		Q[r].push_back({l, i});
	}
	
	for(int R = n; R; --R) {
	
		for(auto& x : Q[R]) cnt[x.second] = st.query(x.first, R);
	
		int last = R;
		
		for(auto& y : a[R]) {
			int mask = y.first, L = y.second;
			int x = sqrt(mask);
			if(x * x == mask) st.upd(L, last, -1);
			last = L - 1;
		}
	}
	
	for(auto ans : cnt) cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}