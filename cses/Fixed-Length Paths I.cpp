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
 
i64 paths;
int n, k;
 
namespace Centroid {
	const int N = 2e5 + 10;
	vector<int> adj[N];
	int n, parCD[N], sz[N];
	
	void init(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) adj[i].clear();
	}
 
	void add_edge(int u, int v) {
		adj[u].pb(v);
		adj[v].pb(u);
	}
 
	int findCentroid(int n, int u) {
		int p = -1;
		while(true) {
			ii heavy(-1, -1);
			for(int v : adj[u]) if(v != p) heavy = max(heavy, ii(sz[v], v));
			if(max(n - sz[u], heavy.fi) <= n / 2) break;
			p = u, u = heavy.sc;
		}
		return u;
	}
 
	void dfssize(int u, int p) {
		sz[u] = 1;
		for(int v : adj[u]) {
			if(v == p) continue;
			dfssize(v, u);
			sz[u] += sz[v];
		}
	}
 
	int depth[N], frq[2][N];
 
	void query(int u, int p) {
		++frq[1][depth[u]];
		paths += frq[0][k-depth[u]];
		if(depth[u] == k) return;
		for(int v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			query(v, u);
		}
	}
 
	void build(int u = 0, int p = -1) {
		for(int& v : adj[u]) if(v == p) swap(v, adj[u].back());
 
		if(p != -1) adj[u].pop_back();
 
		dfssize(u, -1);
		
		int c = findCentroid(sz[u], u);
		
		parCD[c] = p;
 
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < sz[u]; ++j)
				frq[i][j] = 0;
 
		frq[0][0] = 1;
 
		for(int v : adj[c]) {
			depth[v] = 1;
			query(v, c);
			for(int i = 1; frq[1][i]; ++i) {
				frq[0][i] += frq[1][i];
				frq[1][i] = 0;
			}
		}
 
		for(int i = 0; frq[0][i]; ++i) frq[0][i] = 0;
		
		for(int v : adj[c]) build(v, c);
	}
 
	vector<vector<int>> get_centroid_tree() {
		vector<vector<int>> g(n);
		for(int v = 0; v < n; ++v) if(parCD[v] != -1) g[parCD[v]].pb(v);
		return g;
	}
};
 
void solve() {
 
	cin >> n >> k;
 
	Centroid :: init(n);
 
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		Centroid :: add_edge(u, v);
	}
 
	Centroid :: build();
 
	cout << paths << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
