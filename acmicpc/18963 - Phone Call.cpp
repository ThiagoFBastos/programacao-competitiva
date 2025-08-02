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

const int N = 1e5 + 10;

int n, m, tms;
int head[N], in[N], sz[N], depth[N], par[N], root[N], rnk[N], ssz[N];
i64 cost[N];
set<ii> s;
vector<int> adj[N];

int findSet(int u) {
	return u == root[u] ? u : root[u] = findSet(root[u]);
}

void join(int a, int b, int w) {
	a = findSet(a); b = findSet(b);
	if(a == b) return;
	if(rnk[a] > rnk[b]) swap(a, b);
	ssz[b] += ssz[a];
	rnk[b] += rnk[a] == rnk[b];
	root[a] = b;
	cost[b] += cost[a] + w;
}

void updSet(int l, int r, int w) {
	auto it = s.lower_bound(ii(l, -1));
	while(it != s.end() && it->fi <= r) {
		auto [t, v] = *it;
		join(v, adj[v][0], w);
		it = s.erase(it);
	} 
}

void updPath(int a, int b, int w) {
	while(head[a] != head[b]) {
		if(depth[head[a]] > depth[head[b]]) swap(a, b);
		updSet(in[head[b]], in[b] - 1, w);
		join(head[b], par[head[b]], w);
		b = par[head[b]];
	}
	if(depth[a] > depth[b]) swap(a, b);
	updSet(in[a], in[b] - 1, w);
}
	
void dfssize(int u, int p) {
	int t = 1;
	par[u] = p;
	for(int& v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfssize(v, u);
		t += sz[v];
		if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
	}
	sz[u] = t;
}

void dfshld(int u, int p) {
	in[u] = tms++;
	for(int v : adj[u]) {
		if(v == p) continue;	
		else if(2 * sz[v] >= sz[u]) {
			s.emplace(in[u], u);
			head[v] = head[u];
		}
		dfshld(v, u);
	}
}

void init() {
	for(int i = 0; i < n; ++i) {
		root[i] = head[i] = i;
		ssz[i] = 1;
	}
	dfssize(0, 0);	
	dfshld(0, 0);
}

void solve() {
	
	cin >> n >> m;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v); adj[v].pb(u);
	}

	init();

	vector<tuple<int, int, int, int, int>> e(m);

	for(int i = 0; i < m; ++i) {
		int a, b, c, d, w;
		cin >> a >> b >> c >> d >> w;
		--a, --b, --c, --d;
		e[i] = {w, a, b, c, d};
	}

	sort(all(e));

	for(auto& X : e) {
		auto [w, a, b, c, d] = X;
		updPath(a, b, w);
		updPath(c, d, w);
		join(a, c, w);
	}

	int r = findSet(0);
	cout << ssz[r] << ' ' << cost[r] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}