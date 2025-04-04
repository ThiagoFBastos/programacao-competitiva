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
//using i128 = __int128;

namespace LCA {
	const int N = 1e5 + 10, K = 18;
	vector<ii> adj[N];
	int depth[N], tourpos[N], n, tourlen;
	ii sp[K][2*N];
	i64 cost[N];

	void init(int _n) {
		n = _n;
		tourlen = 0;
		for(int i = 0; i < n; ++i) {
			adj[i].clear();
			tourpos[i] = -1;
		}
	}

	void add(int u, int v, int w = 1) {
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}

	int lca(int u, int v) {
		if(tourpos[u] > tourpos[v]) swap(u, v);
		u = tourpos[u], v = tourpos[v];
		int k = 31 - __builtin_clz(v - u + 1);
		return min(sp[k][u], sp[k][v - (1 << k) + 1]).sc;
	}
	
	i64 weightedDist(int u, int v) {
		return cost[u] + cost[v] - 2 * cost[lca(u, v)];
	}

	int dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}

	bool existsPath(int a, int b, int c) {
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
		tourpos[u] = tourlen;
		sp[0][tourlen++] = {depth[u], u};
		for(auto& e : adj[u]) {
			int v = e.fi, w = e.sc;
			if(tourpos[v] != -1) continue;
			cost[v] = cost[u] + w;
			depth[v] = 1 + depth[u];
			dfs(v);
			sp[0][tourlen++] = {depth[u], u};
		}
	}

	void build(int root) {
		cost[root] = depth[root] = 0;
		dfs(root);
		for(int i = 1; (1 << i) <= tourlen; ++i)
			for(int j = 0; j + (1 << i) <= tourlen; ++j)
				sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
	}
};

void solve() {
	int n, q;

	while(true) {
		cin >> n;
		
		if(!n) break;

		LCA :: init(n);

		for(int i = 1; i < n; ++i) {
			int p, len;
			cin >> p >> len;
			LCA :: add(i, p, len);
		}

		LCA :: build(0);

		cin >> q;

		while(q--) {
			int s, t;
			cin >> s >> t;
			cout << LCA :: weightedDist(s, t);	
			if(q) cout << ' ';
		}

		cout << '\n';
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