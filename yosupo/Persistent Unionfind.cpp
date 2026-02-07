#include "bits/stdc++.h"
using namespace std;

using T = tuple<int, int, int>;

struct DSU {
	vector<int> p, rank;
	stack<T> st;
	
	DSU() {}
	
	DSU(int n) {
		p.resize(n);
		rank.assign(n, 0);
		iota(p.begin(), p.end(), 0);
	}
	
	int findSet(int v) {
		return v == p[v] ? v : findSet(p[v]);
	}
	
	bool join(int u, int v) {
		u = findSet(u);
		v = findSet(v);
		if(u == v) return false;
		else if(rank[u] > rank[v]) swap(u, v);
		st.push({u, v, rank[v]});
		p[u] = v;
		rank[v] += rank[u] == rank[v];
		return true;
	}
	
	void backward() {
		auto [u, v, r] = st.top();
		st.pop();
		p[u] = u;
		rank[v] = r;
	}
};


vector<vector<int>> g;
vector<T> event;
vector<int> ans;

DSU dsu;

void dfs(int u) {
	auto [t, x, y] = event[u];
	
	bool flag = false;
	
	if(t == 0) flag = dsu.join(x, y);
	else if(t == 1) ans[u - 1] = dsu.findSet(x) == dsu.findSet(y);
	
	for(int v : g[u]) dfs(v);
	
	if(flag) dsu.backward();
}

void solve() {
	int n, q;
	cin >> n >> q;
	
	dsu = DSU(n);
	
	g.resize(q + 1);
	event.resize(q + 1);
	ans.assign(q, -1);
	
	event[0] = {-2, 0, 0};
	
	for(int i = 0; i < q; ++i) {
		int t, k, u, v;
		cin >> t >> k >> u >> v;
		g[k + 1].push_back(i + 1);
		event[i + 1] = {t, u, v};
	}
	
	dfs(0);
	
	for(int x : ans) if(x >= 0) cout << x << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}