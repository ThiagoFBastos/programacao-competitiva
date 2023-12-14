#include "bits/stdc++.h"
 
using namespace std;
 
#define INF    1000000000
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
using i128 = __int128;
 
void solve() {
	int n, m;
 
	cin >> n >> m;
 
	vector<vector<int>> adj(n), adjSCC(n);
	vector<int> scc(n, -1), low(n), t(n, -1), sz(n, 0), st;
	int tms = 0, n_scc = 0;
 
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		adj[a - 1].pb(b - 1);
	}
 
	auto dfsSCC = [&](auto& self, int u)->void {
		low[u] = t[u] = tms++;
		st.pb(u);
		for(int v : adj[u]) {
			if(t[v] < 0) {
				self(self, v);
				low[u] = min(low[u], low[v]);
			} else if(scc[v] < 0) low[u] = min(low[u], low[v]);
		}	
		if(t[u] != low[u]) return;	
		while(true) {
			int v = st.back(); st.pop_back();
			scc[v] = n_scc;
			++sz[n_scc];
			if(v == u) break;
		}
		++n_scc;
	};
 
	auto dfs = [&](auto& self, int u)->bool {		
		bool flag = sz[u] > 1;
		t[u] = 0;
		for(int v : adjSCC[u]) {
			if(t[v] != -1) continue; 
			if(self(self, v)) flag = true;
		}
		return flag;
	};
 
	for(int i = 0; i < n; ++i) if(t[i] < 0) dfsSCC(dfsSCC, i);
 
	for(int i = 0; i < n; ++i) {
		for(int j : adj[i]) {
			if(scc[i] == scc[j]) continue;
			adjSCC[scc[j]].pb(scc[i]);
			adjSCC[scc[i]].pb(scc[j]);
		}
	}
 
	fill(all(t), -1);
 
	int ans = n;
	for(int i = 0; i < n_scc; ++i) if(t[i] < 0 && !dfs(dfs, i)) --ans;
	
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
