
#include "bits/stdc++.h"

using namespace std;

struct DSU {
	vector<int> par, rank;
	DSU(int n) {
		par.resize(n);
		rank.resize(n);
		for(int v = 0; v < n; ++v) {
			par[v] = v;
			rank[v] = 0;
		}
	}
	
	int find_set(int v) {
		return v == par[v] ? v : par[v] = find_set(par[v]);
	}
	
	void join(int a, int b) {
		a = find_set(a), b = find_set(b);
		if(rank[a] > rank[b]) swap(a, b);
		rank[b] += rank[a] == rank[b];
		par[a] = b;
	}
};

using ii = pair<int, int>;
int n, q;

vector<vector<ii>> g;
vector<int> cost;

void dfs(int u, int p) {
	for(auto& e : g[u]) {
		int v = e.first, w = e.second;
		if(v == p) continue;
		cost[v] = cost[u] ^ w;
		dfs(v, u);
	}
}

void solve() {
	
	cin >> n >> q;
	
	vector<tuple<int, int, int, int>> queries(q);
	g = vector<vector<ii>>(n);
	cost.assign(n, -1);
	
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
	}
	
	DSU dsu(n);
	
	for(int i = 0; i < q; ++i) {
		int t, u, v, r;
		cin >> t >> u >> v;
		--u, --v;
		if(t == 1) {
			cin >> r;
			if(dsu.find_set(u) != dsu.find_set(v)) {
				dsu.join(u, v);
				g[u].push_back({v, r});
				g[v].push_back({u, r});
			}
		}
		queries[i] = {t, u, v, r};
	}
	
	for(int v = 0; v < n; ++v) {
		if(cost[v] != -1) continue;
		cost[v] = 0;
		dfs(v, v);
	}

	dsu = DSU(n);
	
	for(auto& tup : queries) {
		int t, u, v, r;
		tie(t, u, v, r) = tup;

		int pu = dsu.find_set(u);
		int pv = dsu.find_set(v);
		
		if(t == 1) {
			if(pu != pv) {
				cout << "AC\n";
				dsu.join(pu, pv);
			} else cout << ((cost[u] ^ cost[v]) != r ? "WA\n" : "AC\n");
		} else if(pu != pv) cout << "-1\n";
		else cout << (cost[u] ^ cost[v]) << '\n';
	}
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}