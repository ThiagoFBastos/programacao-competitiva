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


void solve() {

	int n, m, k, l;

	cin >> n >> m >> k >> l;

	vector<vector<ii>> adj(n);

	vector<int> a(n), nat[2];
	vector<i64> cost[2];
	priority_queue<tuple<i64, int, int>> pq;

	for(int i = 0; i < 2; ++i) {
		cost[i].assign(n, -1);
		nat[i].assign(n, -1);
	}
	
	for(int& v : a) cin >> v;
	
	for(int i = 0; i < l; ++i) {
		int b;
		cin >> b;
		--b;
		pq.emplace(0LL, b, a[b]);
	}

	for(int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		--u, --v;	
		adj[u].emplace_back(v, c);
		adj[v].emplace_back(u, c);
	}

	while(!pq.empty()) {
		auto [c, u, n] = pq.top();
		pq.pop();
		
		c *= -1;
		
		if(cost[0][u] < 0) {
			nat[0][u] = n;
			cost[0][u] = c;
		} else if(cost[1][u] < 0) {
			if(n == nat[0][u]) continue;
			nat[1][u] = n;
			cost[1][u] = c;
		} else continue;

		for(auto [b, w] : adj[u]) {
			if(cost[1][b] >= 0) continue;
			pq.emplace(-w - c, b, n);
		}
	}

	for(int i = 0; i < n; ++i) {
		if(cost[0][i] < 0 || nat[0][i] == a[i] && cost[1][i] < 0) {
			cout << "-1 ";
			continue;
		}
		cout << cost[nat[0][i] == a[i]][i] << ' ';
	}

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
