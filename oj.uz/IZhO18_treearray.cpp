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
 
const int N = 2e5 + 100, K = 18;
 
int sp[K][N], depth[N], a[N], n, m, q;
 
vector<int> adj[N];
 
set<tuple<int, int, int>> S;
 
void dfs(int u, int p) {
	sp[0][u] = p;
	for(int i = 1; (1 << i) < n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}
}
 
int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) v = sp[i][v];
	if(u == v) return u;
	for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u], v = sp[i][v];
	}
	return sp[0][u];
}
 
void solve() {
	cin >> n >> m >> q;
 
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v); adj[v].pb(u);
	}
 
	dfs(0, 0);
 
	for(int i = 0; i < m; ++i) {
		cin >> a[i];
		--a[i];
		S.emplace(a[i], i, i);
		if(i) S.emplace(lca(a[i], a[i - 1]), i - 1, i);
	}
 
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int pos, v;
			cin >> pos >> v;
			--pos, --v;
			if(pos) S.erase(make_tuple(lca(a[pos], a[pos - 1]), pos - 1, pos));
			if(pos + 1 < m) S.erase(make_tuple(lca(a[pos], a[pos + 1]), pos, pos + 1));
			S.erase(make_tuple(a[pos], pos, pos));
			a[pos] = v;
			S.insert(make_tuple(a[pos], pos, pos));
			if(pos) S.insert(make_tuple(lca(a[pos], a[pos - 1]), pos - 1, pos));
			if(pos + 1 < m) S.insert(make_tuple(lca(a[pos], a[pos + 1]), pos, pos + 1));
		} else {
			int l, r, v;
			cin >> l >> r >> v;
			--l, --r, --v;
			auto it = S.lower_bound(make_tuple(v, l, l));
			if(it == S.end() || get<0>(*it) != v || get<2>(*it) > r) {
				cout << "-1 -1\n";
				continue;
			}
			cout << 1 + get<1>(*it) << ' ' << 1 + get<2>(*it) << '\n';
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
