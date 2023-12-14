#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 1e5 + 100, K = 17, M = 1 << 18;
const i64 L = 1e14L + 10;
 
vector<ii> adj[N];
int sp[K][N], depth[N], in[N], out[N], t;
int n, s, q, e;
i64 pre[N];
 
void dfs(int u, int p) {
	in[u] = t++;
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		pre[t] = pre[in[u]] + w;
		dfs(v, u);
	}
	out[u] = t - 1;		
}
 
int LCA(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) v = sp[i][v];
	if(u == v) return u;
	for(int i = 31 - __builtin_clz(n); i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u], v = sp[i][v];
	}
	return sp[0][u];
}
 
i64 dist(int a, int b) {
	return pre[in[a]] + pre[in[b]] - 2 * pre[in[LCA(a, b)]];
}
 
bool is_on_path(int a, int b, int c) {
	return dist(a, c) + dist(c, b) == dist(a, b);
}
 
i64 st[M], lazy[M];
 
void push(int k) {
	if(!lazy[k]) return;
	for(int i : {2*k,2*k+1}) {
		st[i] += lazy[k];
		lazy[i] += lazy[k];
	}
	lazy[k] = 0;
}
 
void build(int l, int r, int k = 1) {
	lazy[k] = 0;
	if(l == r) st[k] = pre[l];
	else {
		int m = (l + r) / 2;
		build(l, m, 2 * k);
		build(m + 1, r, 2 * k + 1);
		st[k] = min(st[2*k], st[2*k+1]);
	}
}
 
void upd(int l, int r, int x, int lo, int hi, int k = 1) {
	if(l > r) return;
	else if(hi - lo == r - l) {
		st[k] += x;
		lazy[k] += x;
	} else {
		int m = (lo + hi) / 2;
		push(k);
		upd(l, min(r, m), x, lo, m, 2 * k);
		upd(max(m + 1, l), r, x, m + 1, hi, 2 * k + 1);
		st[k] = min(st[2*k], st[2*k+1]);
	}
}
 
i64 query(int l, int r, int lo, int hi, int k = 1) {
	if(l > r) return INFLL;
	else if(hi - lo == r - l) return st[k];
	int m = (lo + hi) / 2;
	push(k);
	return min(query(l, min(r, m), lo, m, 2 * k), query(max(m + 1, l), r, m + 1, hi, 2 * k + 1));
}
 
vector<ii> queries[N];
ii ed[N];
i64 ans[N];
 
void dfsquery(int u, int p) {
 
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		
		upd(in[v], out[v], -w, 0, n - 1);
		upd(0, in[v] - 1, w, 0, n - 1);
		upd(out[v] + 1, n - 1, w, 0, n - 1);
		
		dfsquery(v, u);
 
		upd(in[v], out[v], w, 0, n - 1);
		upd(0, in[v] - 1, -w, 0, n - 1);
		upd(out[v] + 1, n - 1, -w, 0, n - 1);
	}
 
	for(auto [ed_pos, k] : queries[u]) {
		auto [x, y] = ed[ed_pos];
		i64 cost;
 
		if(depth[x] < depth[y]) swap(x, y);	
		
		if(in[u] < in[x] || in[u] > out[x])
			cost = min(query(0, in[x] - 1, 0, n - 1), query(out[x] + 1, n - 1, 0, n - 1));
		else
			cost = query(in[x], out[x], 0, n - 1);
 
		ans[k] = cost;
	}
}
 
void solve() {
	cin >> n >> s >> q >> e;
 
	--e;
 
	for(int i = 1; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		ed[i - 1] = {a, b};
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}
 
	dfs(0, 0);
 
	vector<bool> shop(n, false);
 
	for(int i = 0; i < s; ++i) {
		int v;
		cin >> v;
		shop[--v] = true;
	}
 
	for(int i = 0; i < q; ++i) {
		int ed_pos, src;
		cin >> ed_pos >> src;
		--src, --ed_pos;
		auto [u, v] = ed[ed_pos];
		if(is_on_path(src, e, u) && is_on_path(src, e, v))
			queries[src].pb({ed_pos, i});
		else
			ans[i] = -1;
	}
 
	for(int i = 0; i < n; ++i) if(!shop[i]) pre[in[i]] = INFLL;
 
	build(0, n - 1);
	dfsquery(0, 0);
 
	for(int i = 0; i < q; ++i) {
		if(ans[i] < 0) cout << "escaped\n";
		else if(ans[i] > L) cout << "oo\n";
		else cout << ans[i] << '\n';
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
