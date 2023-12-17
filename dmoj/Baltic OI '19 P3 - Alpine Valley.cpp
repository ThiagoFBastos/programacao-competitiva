#include "bits/stdc++.h"

using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e5 + 100, K = 17;

ii ed[N];
vector<ii> adj[N];
int n, s, q, e;
int in[N], out[N], t;
int sp[K][N], depth[N];
i64 pre[N], cost[N];

void dfsPrecalc(int u, int p) {
	in[u] = t++;
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		pre[v] = w + pre[u];
		depth[v] = 1 + depth[u];
		dfsPrecalc(v, u);
	}
	out[u] = t - 1;
}

i64 st[4 * N], lazy[4 * N];

void build(int lo, int hi, int n = 1) {
	if(lo == hi) st[n] = cost[lo];
	else {
		int m = (lo + hi) / 2;		
		build(lo, m, 2 * n);
		build(m + 1, hi, 2 * n + 1);
		st[n] = min(st[2 * n], st[2 * n + 1]);
	}
}

void push(int n) {
	for(int i : {2 * n, 2 * n + 1}) {
		lazy[i] += lazy[n];
		st[i] += lazy[n];
	}
	lazy[n] = 0;
}

void upd(int l, int r, int x, int lo, int hi, int n = 1) {
	if(l > r || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		st[n] += x;
		lazy[n] += x;
		return;
	}
	int m = (lo + hi) / 2;
	push(n);
	upd(l, r, x, lo, m, 2 * n);	
	upd(l, r, x, m + 1, hi, 2 * n + 1);
	st[n] = min(st[2 * n], st[2 * n + 1]);
}

i64 query(int l, int r, int lo, int hi, int n = 1) {
	if(l > r || r < lo || l > hi) return INFLL;
	else if(lo >= l && hi <= r) return st[n];
	int m = (lo + hi) / 2;
	push(n);
	i64 s = query(l, r, lo, m, 2 * n);
	i64 t = query(l, r, m + 1, hi, 2 * n + 1);
	return min(s, t);
}	

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) b = sp[i][b];
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(n); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

bool isParent(int a, int b) {
	return lca(a, b) == a;
}

i64 dist(int a, int b) {
	return pre[a] + pre[b] - 2 * pre[lca(a, b)];
}

vector<ii> qry[N];
i64 queryAns[N];

void dfsQuery(int u, int p) {

	for(auto [block, pos] : qry[u]) {
		if(isParent(block, u))
			queryAns[pos] = query(in[block], out[block], 0, n - 1);
		else
			queryAns[pos] = min(query(0, in[block] - 1, 0, n - 1), query(out[block] + 1, n - 1, 0, n - 1));
	}


	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
			
		upd(0, in[v] - 1, w, 0, n - 1);
		upd(in[v], out[v], -w, 0, n - 1);
		upd(out[v] + 1, n - 1, w, 0, n - 1);

		dfsQuery(v, u);
		
		upd(0, in[v] - 1, -w, 0, n - 1);
		upd(in[v], out[v], w, 0, n - 1);
		upd(out[v] + 1, n - 1, -w, 0, n - 1);
	}
}

void solve() {
	cin >> n >> s >> q >> e;

	for(int i = 1; i < n; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		--a, --b;
		ed[i] = {a, b};
		adj[a].pb({b, w});
		adj[b].pb({a, w});
	}
	
	dfsPrecalc(0, 0);

	fill(cost, cost + N, INFLL);

	while(s--) {
		int a;
		cin >> a;
		--a;
		cost[in[a]] = pre[a];
	}

	build(0, n - 1);

	--e;

	for(int i = 0; i < q; ++i) {
		int a, b;

		cin >> a >> b;

		--b;

		auto [x, y] = ed[a];

		if(depth[x] < depth[y]) swap(x, y);
	
		if(isParent(x, b)) {
			if(!isParent(x, e)) qry[b].pb({x, i});
			else queryAns[i] = -1;
		} else if(dist(b, e) == dist(b, x) + dist(x, e)) qry[b].pb({x, i});
		else queryAns[i] = -1;
	}

	dfsQuery(0, 0);
	
	const i64 L = 1e17L;
	
	for(int i = 0; i < q; ++i) {
		if(queryAns[i] == -1) cout << "escaped\n";
		else if(queryAns[i] >= L) cout << "oo\n";
		else cout << queryAns[i] << '\n';
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
