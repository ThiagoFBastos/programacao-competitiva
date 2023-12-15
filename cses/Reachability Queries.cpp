#include "bits/stdc++.h"
using namespace std;
int n, m, q, tms, cnt;
vector<vector<int>> G, dag, idag;
vector<int> lo, scc;
stack<int> st;
void dfs(int u) {
	int t;
	lo[u] = t = tms++;
	st.push(u);
	for(int v : G[u]) {
		if(lo[v] == -1) {
			dfs(v);
			lo[u] = min(lo[u], lo[v]);		
		} else if(scc[v] == -1) lo[u] = min(lo[u], lo[v]);
	}
	if(t == lo[u]) {
		while(true) {
			int v = st.top();
			scc[v] = cnt;
			st.pop();
			if(v == u) break;
		}
		++cnt;
	}
}
vector<bool> vis;
vector<int> topo;
void topo_sort(int u) {
	vis[u] = true;
	for(int v : dag[u]) {
		if(vis[v]) continue;
		topo_sort(v);
	}
	topo.push_back(u);
}
const int MAXN = 5e4;
bitset<MAXN> ch[MAXN];
void solve() {
	cin >> n >> m >> q;
	G.resize(n);
	lo.assign(n, -1);
	scc.assign(n, -1);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
	}
	for(int v = 0; v < n; ++v) if(lo[v] == -1) dfs(v);
	dag.resize(cnt);
	idag.resize(cnt);
	vis.assign(cnt, false);
	for(int u = 0; u < n; ++u) {
		for(int v : G[u]) {
			if(scc[u] == scc[v]) continue;
			dag[scc[u]].push_back(scc[v]);
			idag[scc[v]].push_back(scc[u]);
		}
	}
	for(int v = 0; v < cnt; ++v) {
		ch[v][v] = 1;
		if(!vis[v]) topo_sort(v);
	}
	for(int v : topo)
		for(int u : idag[v])
			ch[u] |= ch[v];
	while(q--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		cout << (ch[scc[u]][scc[v]] ? "YES\n" : "NO\n");
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	solve();
	return 0;
}
