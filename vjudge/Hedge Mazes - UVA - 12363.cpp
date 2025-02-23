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

namespace GraphCut {
	const int N = 1e4 + 10;
	vector<ii> adj[N];
	int n, t, ncc, ned, low[N], in[N], cc[N];
	bool cut_v[N], cut_e[N];

	void init(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) {
			adj[i].clear();
			in[i] = -1;
			cut_v[i] = false;
		}
		ned = t = ncc = 0;
	}

	void add_edge(int u, int v) {
		cut_e[ned] = false;
		adj[u].pb({v, ned});
		adj[v].pb({u, ned});
		++ned;	
	}

	int dfs(int u, int ed) {
		int subs = 0;
		in[u] = low[u] = t++;
		cc[u] = ncc;
		for(auto& edge : adj[u]) {
			int v = edge.fi, e = edge.sc;
			if(in[v] == -1) {
				++subs;
				(void)dfs(v, e);
				cut_v[u] = cut_v[u] || low[v] >= in[u];
				cut_e[e] = low[v] > in[u];
				low[u] = min(low[u], low[v]);
			} else if(e != ed)
				low[u] = min(low[u], in[v]);
		}
		return subs;
	}

	bool sameCC(int u, int v) {
		return cc[u] == cc[v];
	}

	void build() {
		for(int v = 0; v < n; ++v) {
			if(in[v] != -1) continue;
			int subs = dfs(v, -1);
			cut_v[v] = cut_v[v] && subs > 1;
			++ncc;
		}
	}

	bool is_cut_vertex(int v) {
		return cut_v[v];
	}

	bool is_cut_edge(int u, int v) {
		if(in[u] > in[v]) swap(u, v);
		return cc[u] == cc[v] && low[v] > in[u];
	}

	vector<int> get_cut_vertexes() {
		vector<int> cut;
		for(int v = 0; v < n; ++v) if(cut_v[v]) cut.pb(v);
		return cut;
	}

	vector<ii> get_cut_edges() {
		vector<ii> cut;
		for(int u = 0; u < n; ++u) {
			for(auto [v, e] : adj[u]) {
				if(u > v || !cut_e[e]) continue;
				cut.pb({u, v});
			}
		}
		return cut;
	}
};

namespace LCA {
	const int N = 1e4 + 10, K = 14;
	vector<ii> adj[N];
	int depth[N], cost[N], par[K][N], n;
	bool vis[N];

	void init(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) {
			adj[i].clear();
			vis[i] = false;
		}
	}

	void add_edge(int u, int v, int w = 1) {
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}

	int goUp(int v, int d) {
		for(; d > 0; d -= d & -d) v = par[__builtin_ctz(d)][v];
		return v;
	}

	int lca(int u, int v) {
		if(depth[u] > depth[v]) swap(u, v);
		v = goUp(v, depth[v] - depth[u]);
		if(u == v) return u;
		for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
			if(par[i][u] == par[i][v]) continue;
			u = par[i][u], v = par[i][v];
		}
		return par[0][u];
	}
	
	int weightedDist(int u, int v) {
		return cost[u] + cost[v] - 2 * cost[lca(u, v)];
	}

	int dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}

	int kth_node_path(int a, int b, int k) {
		int c = lca(a, b), d = depth[a] + depth[b] - 2 * depth[c];
		if(k <= depth[a] - depth[c] + 1) return goUp(a, k - 1);
		return goUp(b, d + 1 - k);
	}

	bool exists_path(int a, int b, int c) {
		vector<int> p {a, b, c};
		for(int i = 0; i < 3; ++i) {
			for(int j = i + 1; j < 3; ++j) {
				int k = i ^ j ^ 3;
				if(dist(p[i], p[j]) == dist(p[i], p[k]) + dist(p[j], p[k]))
					return true;
			}
		}
		return false;
	}

	void dfs(int u) {	
		vis[u] = true;
		for(int i = 1; (1 << i) <= n; ++i) par[i][u] = par[i - 1][par[i - 1][u]];
		for(auto& e : adj[u]) {
			int v = e.fi, w = e.sc;
			if(vis[v]) continue;
			par[0][v] = u;
			cost[v] = cost[u] + w;
			depth[v] = 1 + depth[u];
			dfs(v);
		}
	}

	void build(int root) {
		par[0][root] = root;
		cost[root] = depth[root] = 0;
		dfs(root);
	}
};

void solve() {
	int n, m, q;

	cin >> n >> m >> q;

	if(n + m + q == 0) exit(0);

	vector<ii> edges(m);

	LCA :: init(n);
	GraphCut :: init(n);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		GraphCut :: add_edge(u, v);
		edges[i] = {u, v};
	}

	GraphCut :: build();
	
	for(int i = 0; i < m; ++i) {
		int u = edges[i].fi, v = edges[i].sc;
		LCA :: add_edge(u, v, GraphCut :: is_cut_edge(u, v) ? 0 : 1);
	}
	
	LCA :: build(0);

	while(q--) {
		int s, t;
		cin >> s >> t;
		--s, --t;
		cout << (!GraphCut :: sameCC(s, t) || LCA :: weightedDist(s, t) ? "N\n" : "Y\n");
	}

	cout << "-\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}