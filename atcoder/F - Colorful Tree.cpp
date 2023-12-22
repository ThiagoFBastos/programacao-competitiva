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

const int N = 1e5 + 100;

struct node {
	i64 sum;
	int cnt;
	node *l, *r;
};

int n, q, sp[17][N];
vector<node*> st;
vector<vector<tuple<int, int, int>>> adj;
vector<i64> cost;
vector<int> depth;

node *upd(int k, int x, int l, int r, node *p) {
	auto no = new node;
	no->sum = x + p->sum;
	no->cnt = 1 + p->cnt;
	no->l = p->l, no->r = p->r;
	if(l != r) {
		int mid = (l + r) >> 1;
		if(k <= mid) no->l = upd(k, x, l, mid, p->l);
		else no->r = upd(k, x, mid + 1, r, p->r);
	}
	return no;
}

i64 query_sum(int k, int l, int r, node *a, node *b) {
	if(l == r) return b->sum - a->sum;
	int mid = (l + r) / 2;
	return k <= mid ? query_sum(k, l, mid, a->l, b->l) : query_sum(k, mid + 1, r, a->r, b->r);	
}

int query_cnt(int k, int l, int r, node *a, node *b) {
	if(l == r) return b->cnt - a->cnt;
	int mid = (l + r) / 2;
	return k <= mid ? query_cnt(k, l, mid, a->l, b->l) : query_cnt(k, mid + 1, r, a->r, b->r);	
}

node *init(int l, int r) {
	auto no = new node;
	no->cnt = no->sum = 0;
	if(l != r) {
		int mid = (l + r) >> 1;
		no->l = init(l, mid);
		no->r = init(mid + 1, r);
	}
	return no;
}	

void dfs(int u, int p) {
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(auto [v, c, w] : adj[u]) {
		if(v == p) continue;
		st[v] = upd(c, w, 0, n - 1, st[u]);
		cost[v] = cost[u] + w;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}
}

int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int i = 0; (1 << i) <= d; ++i) if(d & 1 << i) v = sp[i][v];
	if(u == v) return u;
	for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u], v = sp[i][v];
	}
	return sp[0][u];
}

void solve() {
	cin >> n >> q;
	adj.resize(n);
	cost.assign(n, 0);
	depth.assign(n, 0);
	st.resize(n);
	for(int i = 1; i < n; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		--a, --b;
		adj[a].emplace_back(b, c, d);
		adj[b].emplace_back(a, c, d);
	}
	st[0] = init(0, n - 1);
	dfs(0, 0);
	while(q--) {
		int u, v, w, x, y;
		cin >> x >> y >> u >> v;
		--u, --v;
		w = lca(u, v);
		i64 ans = cost[u] + cost[v] - 2 * cost[w];
		i64 sum = query_sum(x, 0, n - 1, st[w], st[u]) + query_sum(x, 0, n - 1, st[w], st[v]);
		int cnt = query_cnt(x, 0, n - 1, st[w], st[u]) + query_cnt(x, 0, n - 1, st[w], st[v]);
		cout << ans - sum + (i64)cnt * y << '\n';
	}
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(t--) solve();
}
