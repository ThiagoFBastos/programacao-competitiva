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
 
int n, m, k, q;
vector<vector<ii>> G;
 
auto dijkstra(vector<int>& v) {
	priority_queue<pair<i64, int>> pq;
	vector<i64> cost(n, -1);
	for(int u : v) pq.emplace(0LL, u);
	while(!pq.empty()) {
		auto [c, v] = pq.top();
		pq.pop();
		c *= -1;
		if(cost[v] != -1) continue;
		cost[v] = c;
		for(auto [u, w] : G[v]) {
			if(cost[u] != -1) continue;
			pq.emplace(-c - w, u);
		}
	}
	return cost;
}
 
vector<int> pai, rnk;
vector<i64> lb;
 
int findSet(int v) {
	return v == pai[v] ? v : findSet(pai[v]);
}
 
int depth(int u) {
	return u == pai[u] ? 0 : 1 + depth(pai[u]);
}
 
void join(int u, int v, i64 x) {
	u = findSet(u);
	v = findSet(v);
	if(u == v) return;
	else if(rnk[u] > rnk[v]) swap(u, v);
	lb[u] = x;
	pai[u] = v;
	rnk[v] += rnk[u] == rnk[v];
}
 
void solve() {	
	
	cin >> n >> m;
 
	G.resize(n);
 
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		G[a].emplace_back(b, c);
		G[b].emplace_back(a, c);
	}
 
	cin >> k;
 
	vector<int> npp(k);
 
	for(int& v : npp) {
		cin >> v;
		--v;
	}
 
	auto cost = dijkstra(npp);
 
	vector<pair<i64, int>> s(n);
 
	for(int i = 0; i < n; ++i) s[i] = {cost[i], i};
 
	sort(s.rbegin(), s.rend());
 
	pai.resize(n);
	rnk.assign(n, 0);
	lb.resize(n);
	iota(pai.begin(), pai.end(), 0);
 
	for(auto [c, v] : s) {
		for(auto [u, w] : G[v]) {
			if(make_pair(cost[u], u) > make_pair(c, v))
				join(u, v, c);
		}
	}
 
	cin >> q;
 
	while(q--) {
		int s, t;
		cin >> s >> t;
 
		--s, --t;
 
		int ds = depth(s), dt = depth(t);
		i64 ans = LLONG_MAX;
 
		while(s != t) {
			if(ds > dt) ans = min(ans, lb[s]), s = pai[s], --ds;
			else if(ds < dt) ans = min(ans, lb[t]), t = pai[t], --dt;
			else ans = min(ans, min(lb[s], lb[t])), s = pai[s], t = pai[t];
		}
 
		cout << ans << '\n';
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
