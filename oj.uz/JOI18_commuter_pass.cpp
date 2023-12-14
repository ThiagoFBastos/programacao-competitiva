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
 
const i64 inf = 1e16L;
 
int n, m, s, t, u, v;
vector<ii> edge;
vector<vector<int>> g, dag;
vector<i64> ds, du, dv, dp;
vector<int> state;
i64 ans = inf;
 
auto dijkstra(int s) {
	vector<bool> seen(n, false);
	vector<i64> dist(n, inf);
	priority_queue<pair<i64, int>> pq;
	
	dist[s] = 0;
	pq.emplace(0LL, s);
	
	while(!pq.empty()) {
		auto [cst, v] = pq.top();
		pq.pop();
		if(seen[v]) continue;
		cst *= -1;
		seen[v] = true;
		for(int id : g[v]) {
			auto [u, w] = edge[id];
			if(dist[u] <= cst + w) continue;
			dist[u] = cst + w;
			pq.emplace(-dist[u], u);
		}
	}
	
	return dist;
}
 
vector<int> topo;
 
void dfs(int u) {
	state[u] = 0;
 
	if(u != t) {
		for(int id : dag[u]) {
			auto [v, w] = edge[id];
			
			if(state[v] == -1) dfs(v);
		
			if(state[v] == 1) {
				dp[u] = min(dp[u], dp[v]);
				state[u] = 1;
			}
		}
	}
	
	if(u == t) state[u] = 1;
	
	if(state[u] == 1) {
		dp[u] = min(dp[u], dv[u]);	
		ans = min(ans, du[u] + dp[u]);
		topo.push_back(u);
	}
 
}
 
void solve() {
	
	cin >> n >> m >> s >> t >> u >> v;
	
	--s, --t, --u, --v;
	
	edge.resize(2 * m);
	g.resize(n);
	dag.resize(n);
	state.assign(n, -1);
	dp.assign(n, inf);
	
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		
		--a, --b;
		
		edge[2 * i] = {b, c};
		edge[2 * i + 1] = {a, c};
		
		g[a].push_back(2 * i);
		g[b].push_back(2 * i + 1);
	}
 
	ds = dijkstra(s);
	du = dijkstra(u);
	dv = dijkstra(v);
	
	for(int u = 0; u < n; ++u) {
		for(int id : g[u]) {
			auto [v, w] = edge[id];
			if(ds[v] == ds[u] + w) dag[u].push_back(id);
		}
	}
 
	dfs(s);
	
	ans = min(ans, du[v]);
	
	fill(dp.begin(), dp.end(), inf);
	
	reverse(topo.begin(), topo.end());
	
	for(int v : topo) {
		dp[v] = dv[v];
		for(int id : g[v]) {
			auto [u, w] = edge[id];
			ans = min(ans, du[v] + dp[u]);
			dp[v] = min(dp[v], dp[u]);
		}
	}
	
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
