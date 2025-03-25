#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using edge = tuple<int, int, ll>;
int n, q, tms;
vector<vector<edge>> g;
vector<int> lo, hi;
vector<edge> e;
void dfs(int u, int p = -1) {
	lo[u] = hi[u] = tms++;
	for(auto [v, l, a] : g[u]) {
		if(v == p) continue;
		e.push_back({l, v, a});
		dfs(v, u);
		hi[u] = max(hi[u], hi[v]);
	}
}
struct segtree {
	vector<ll> st;
	int n;
	segtree(int n) {
		this->n = n;
		st.assign(1 << (33 - __builtin_clz(n)), 0);
	}
	void push(int no) {
		if(!st[no]) return;
		int L = no << 1, R = no << 1 | 1;
		st[L] = gcd(st[L], st[no]);
		st[R] = gcd(st[R], st[no]);
		st[no] = 0;
	}
	void upd(ll val, int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return;
		else if(r - l == hi - lo) st[no] = gcd(st[no], val);
		else {
			int mid = (lo + hi) / 2;
			push(no);
			upd(val, l, min(r, mid), lo, mid, no << 1);
			upd(val, max(mid + 1, l), r, mid + 1, hi, no << 1 | 1);
		}
	}
	ll query(int k, int lo, int hi, int no = 1) {
		if(lo == hi) return st[no];
		int mid = (lo + hi) / 2;
		push(no);
		return k <= mid ? query(k, lo, mid, no << 1) : query(k, mid + 1, hi, no << 1 | 1);
	}
	void upd(ll val, int l, int r) {
		upd(val, l, r, 0, n - 1);
	}
	ll query(int k) {
		return query(k, 0, n - 1);
	}
};

void solve() {
	cin >> n >> q;
	g.clear();
	e.clear();
	g.resize(n);
	lo.resize(n);
	hi.resize(n);
	for(int i = 1; i < n; ++i) {
		int u, v, l;
		ll a;
		cin >> u >> v >> l >> a;
		--u, --v;
		g[u].push_back({v, l, a});
		g[v].push_back({u, l, a});
	}
	tms = 0;
	dfs(0);
	sort(e.begin(), e.end());
	vector<tuple<int, int, int>> query(q);
	vector<ll> ans(q);
	for(int i = 0; i < q; ++i) {
		int c, w;
		cin >> c >> w;
		query[i] = {w, c - 1, i};
	}
	sort(query.begin(), query.end());
	int i = 0, j = 0;
	segtree st(n);
	while(j < q) {
		if(i < size(e) && get<0>(e[i]) <= get<0>(query[j])) {
			auto [l, v, a] = e[i++];
			st.upd(a, lo[v], hi[v]);
		} else {
			auto [w, v, k] = query[j++];
			ans[k] = st.query(lo[v]);
		}
	}
	for(ll x : ans) cout << x << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
	return 0;
}