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
 
vector<vector<int>> g;
vector<int> leaves;
int n;
 
void preprocess(int u, int p = -1) {
	leaves[u] = 0;
	if((int)g[u].size() == 1) ++leaves[u];
	for(int v : g[u]) {
		if(v == p) continue;
		preprocess(v, u);
		leaves[u] += leaves[v];
	}
}
 
int dfs(int u, int p = -1) {
	
	int max_leaves = 0;
	
	if(p != -1) max_leaves = leaves[0] - leaves[u];
	
	for(int v : g[u]) {
		if(v == p) continue;
		max_leaves = max(max_leaves, leaves[v]);
	}
	
	if(max_leaves <= leaves[0] / 2) return u;
	
	for(int v : g[u]) {
		if(v == p) continue;
		int w = dfs(v, u);
		if(w != -1) return w;
	}
	
	return -1;
}
 
void solve() {
	cin >> n;
	
	g.resize(n);
	leaves.resize(n);
	
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	preprocess(0);
	
	int v = dfs(0);
 
	vector<vector<int>> F;
	
	function<void(int, int)> get = [&](int u, int p) {
		if(g[u].size() == 1) F.back().push_back(u);
		for(int v : g[u]) {
			if(v == p) continue;
			get(v, u);
		}
	};
		
	for(int u : g[v]) {
		F.push_back({});
		get(u, v);
	}
	
	vector<ii> pairs;
	set<ii> S;
	
	for(int i = 0; i < (int)F.size(); ++i) S.insert({(int)F[i].size(), i});
	
	while(!S.empty()) {
		ii e = *S.begin();
		ii d = *S.rbegin();
		if(e == d) break;
		S.erase(S.begin());
		S.erase(d);
		pairs.emplace_back(F[e.second].back() + 1, F[d.second].back() + 1);
		F[e.second].pop_back();
		F[d.second].pop_back();
		if(--e.first) S.insert(e);
		if(--d.first) S.insert(d);
	}
	
	for(auto& x : F) {
		if(x.empty()) continue;
		int u = x.back();
		for(int v = 0; v < n; ++v) {
			if(v == u || g[v].size() > 1) continue;
			pairs.emplace_back(u + 1, v + 1);
			break;
		}
		break;
	}
	
	cout << pairs.size() << '\n';
	for(auto [u, v] : pairs) cout << u << ' ' << v << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
