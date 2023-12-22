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

struct DSU {
	vector<int> pai, rank, sz;
	
	DSU(int n) {
		pai.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(pai.begin(), pai.end(), 0);
	}
	
	int findSet(int v) {
		return v == pai[v] ? v : pai[v] = findSet(pai[v]);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);
		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		pai[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];
		return true;
	}
};

void solve() {
	
	int n, m;

	cin >> n;

	vector<int> p(n), deg(n, 0);
	vector<vector<ii>> g(n);
	DSU dsu(n);

	for(int& v : p) cin >> v;

	cin >> m;

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(dsu.join(u, v)) {
			++deg[u], ++deg[v];
			g[u].emplace_back(v, i);
			g[v].emplace_back(u, i);
		}
	}
	
	vector<int> swaps, X, Y;

	function<void(int, int)> dfs = [&](int u, int pa) {
		X.push_back(u);
		Y.push_back(p[u]);
		for(auto [v, e] : g[u]) {
			if(v == pa) continue;
			dfs(v, u);
		}
	};

	vector<int> edges, path;

	function<bool(int, int, int)> dfs_sort = [&](int u, int w, int pa) {	
		path.push_back(u);
		if(u == w) {
			while(!path.empty()) {
				swap(p[w], p[path.back()]);
				w = path.back();
				path.pop_back();
			}
			reverse(edges.begin(), edges.end());
			for(int e : edges) swaps.push_back(e);
			return true;
		}
		for(auto [v, e] : g[u]) {
			if(v == pa) continue;
			edges.push_back(e);
			if(dfs_sort(v, w, u)) return true;
			edges.pop_back();
		}
		path.pop_back();
		return false;
	};

	for(int v = 0; v < n; ++v) {
		if(v != dsu.findSet(v)) continue;
		
		queue<int> q;

		X.clear();
		Y.clear();
		
		dfs(v, v);

		sort(X.begin(), X.end());
		sort(Y.begin(), Y.end());
		
		for(int u = 0; u < n; ++u) {
			if(dsu.findSet(u) != v || deg[u] != 1) continue;
			q.push(u);
		}

		while(!q.empty()) {
			int u = q.front(), v = -1;

			q.pop();

			int j = lower_bound(X.begin(), X.end(), u) - X.begin();

			for(int k : X) {
				if(p[k] == Y[j]) {
					v = k;
					break;
				}
			}

			path.clear();
			edges.clear();
			dfs_sort(u, v, u);

			for(auto [v, e] : g[u]) if(--deg[v] == 1) q.push(v);
		}
	}

	if(!is_sorted(p.begin(), p.end())) {
		cout << "-1\n";
		return;
	}

	cout << swaps.size() << '\n';
	for(int c : swaps) cout << c + 1 << ' ';
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
