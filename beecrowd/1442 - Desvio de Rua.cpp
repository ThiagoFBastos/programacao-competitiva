#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

int n, m, t_in, scc_t;
vector<vector<int>> g;
vector<vector<pair<int, int>>> SCC;
vector<int> low, t, scc;
vector<bool> src;
stack<int> s;

void dfs(int v) {
	t[v] = low[v] = t_in++;
	s.push(v);
	for(int u : g[v]) {
		if(t[u] == -1) {
			dfs(u);
			low[v] = min(low[v], low[u]);		
		} else if(scc[u] == -1) low[v] = min(low[v], t[u]);
	}
	if(t[v] == low[v]) {
		while(true) {
			int u = s.top();
			s.pop();
			scc[u] = scc_t;
			if(u == v) break;
		}
		++scc_t;
	}
}

bool ponte;
void dfs(int v, int edge) {
	low[v] = t[v] = t_in++;
	for(auto [u, e] : SCC[v]) {
		if(e == edge) continue;
		else if(t[u] == -1) {
			dfs(u, e);
			if(t[v] < low[u]) ponte = true;
			low[v] = min(low[v], low[u]);
		} else low[v] = min(low[v], t[u]);
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> n >> m) {
		g.resize(n);
		t.assign(n, -1);
		low.resize(n);
		scc.assign(n, -1);
		t_in = scc_t = 0;
		for(int i = 0; i < m; ++i) {
			int a, b, t;
			cin >> a >> b >> t;
			--a, --b;
			if(i == 0) continue;
			else if(t == 1) g[a].push_back(b);
			else {
				g[a].push_back(b);
				g[b].push_back(a);
			}
		}
		for(int i = 0; i < n; ++i) if(t[i] == -1) dfs(i);
		if(scc_t == 1) cout << "-\n";
		else {
			int edge = 0;
			src.assign(scc_t, true);
			SCC.resize(scc_t);
			for(int v = 0; v < n; ++v) {
				for(int u : g[v]) {
					if(scc[u] == scc[v]) continue;
					src[scc[u]] = false;
					SCC[scc[v]].push_back({scc[u], edge});
					SCC[scc[u]].push_back({scc[v], edge++});
				}
			}
			int cnt = count(src.begin(), src.end(), true);
			if(cnt > 1) cout << "*\n";
			else {
				for(int v = 0; v < scc_t; ++v) {
					if(src[v]) {
						t.assign(scc_t, -1);
						low.resize(scc_t);
						ponte = false;
						t_in = 0;
						dfs(v, -1);
						break;
					}	
				}
				cout << (ponte ? 2 : 1) << '\n';
			}
			for(int v = 0; v < scc_t; ++v) SCC[v].clear(); 
		}
		for(int v = 0; v < n; ++v) g[v].clear();
	}
	return 0;
}