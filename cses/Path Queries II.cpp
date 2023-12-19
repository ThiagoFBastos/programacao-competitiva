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
 
struct SegTree {
	vector<int> st;
	int n;
	SegTree() {}
	SegTree(vector<int>& a) {
		n = a.size();
		st.resize(2 * n + 1);
		for(int k = n; k < 2 * n; ++k) st[k] = a[k - n];
		for(int k = n - 1; k > 0; --k) st[k] = max(st[k << 1], st[(k << 1) | 1]);
	}
	void upd(int k, int x) {
		k += n;
		st[k] = x;
		for(k >>= 1; k; k >>= 1) st[k] = max(st[k << 1], st[(k << 1) | 1]);
	}
	int query(int l, int r) {
		int ans {};
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) ans = max(ans, st[l++]);
			if(~r & 1) ans = max(ans, st[r--]);
		}
		return ans;
	}
};
 
struct HLD {
	vector<int> sz, ptr, pos, h, stk;
	vector<vector<int>> sp;
	SegTree st;
	int id = 1;
 
	int lca(int u, int v) {
		if(h[u] > h[v]) swap(u, v);
		for(int k = 0, d = h[v] - h[u]; (1 << k) <= d; ++k) if(d & (1 << k)) v = sp[v][k];
		if(u == v) return u;
		for(int k = 31 - __builtin_clz(h[u]); k >= 0; --k)
			if(sp[u][k] != sp[v][k])
				u = sp[u][k], v = sp[v][k];
		return sp[u][0];
	}
 
	void dfs(vector<vector<int>>& g, int u, int p) {
		sz[u] = 1, sp[u][0] = p;
		for(int i = 1; (1 << i) <= (int)g.size(); ++i) 
			sp[u][i] = sp[sp[u][i - 1]][i - 1];
		for(int v : g[u]) {
			if(v == p) continue;
			h[v] = 1 + h[u];
			dfs(g, v, u);
			sz[u] += sz[v];
		}
	}
 
	void get_paths(vector<vector<int>>& g, int u, int p) {
		for(int v : g[u]) {
			if(v == p) continue;
			get_paths(g, v, u);
		}
		if(ptr[u] != -1) return;
		while(u) {
			int v = sp[u][0];
			stk.push_back(u);
			if(sz[u] < (1 + sz[v]) / 2) {u = v; break;}
			u = v;
		}
		while(!stk.empty()) {
			int v = stk.back();
			stk.pop_back();
			pos[v] = id++, ptr[v] = u;
		}
	}
 
	int query(int a, int b) {
		int c = lca(a, b), ans = 0;
 
		while(h[a] > h[c]) {
			int d = ptr[a];
			int lo = pos[a] - h[a] + h[d] + 1, hi = pos[a];
			if(ptr[c] == ptr[a]) lo = pos[c] + 1;
			ans = max(ans, st.query(lo, hi));
			a = d;
		}
 
		while(h[b] >= h[c]) {
			int d = ptr[b];
			int lo = pos[b] - h[b] + h[d] + 1, hi = pos[b];
			if(ptr[c] == ptr[b]) lo = pos[c];
			ans = max(ans, st.query(lo, hi));
			b = d;
		}
 
		return ans;
	}
 
	void upd(int k, int x) {
		st.upd(pos[k], x);
	}
 
	HLD(vector<vector<int>>& g, vector<int>& value) {
		int n = g.size();
		int lg = 32 - __builtin_clz(n);
		sz.resize(n);
		ptr.assign(n, -1);
		pos.resize(n);
		h.resize(n);
		sp = vector<vector<int>>(n, vector<int>(lg));
		fill(sp[0].begin(), sp[0].end(), 0);
		h[0] = 0, h[1] = 1, pos[0] = 0;
		dfs(g, 1, 0);
		get_paths(g, 1, 0);
		vector<int> e(n);
		for(int i = 0; i < n; ++i) e[pos[i]] = value[i];
		st = SegTree(e);
	}
};
 
void solve() {
	int n, q;
 
	cin >> n >> q;
	
	vector<int> a(n + 1);
	vector<vector<int>> g(n + 1);
 
	for(int i = 1; i <= n; ++i) cin >> a[i];
 
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
 
	HLD hld(g, a);
 
	while(q--) {
		int t, x, y;
		cin >> t >> x >> y;
		if(t == 1) hld.upd(x, y);
		else cout << hld.query(x, y) << ' ';
	}
 
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
