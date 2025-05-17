#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 2e5 + 10;
 
vector<pair<int, int>> adj[N];
int n, m;
 
vector<int64_t> dijkstra() {
	using T = pair<int64_t, int>;
 
	vector<int64_t> cost(n + m, -1);
	priority_queue<T, vector<T>, greater<T>> pq;
 
	pq.emplace(0, 0);
 
	while(!pq.empty()) {
		auto [c, w] = pq.top();
 
		pq.pop();
 
		if(cost[w] != -1)
			continue;
 
		cost[w] = c;
 
		for(auto [v, x] : adj[w]) {
			if(cost[v] != -1)
				continue;
 
			pq.emplace(x + c, v);
		}
	}
 
	cost.erase(cost.begin() + n, cost.end());
 
	return cost;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> m;
 
	vector<int> ticket(m);
 
	for(int& v : ticket) cin >> v;
 
	for(int i = 0; i < m; ++i) {
		int cities;
 
		cin >> cities;
 
		for(int j = 0; j < cities; ++j) {
			int city;
			
			cin >> city;
			
			--city;
 
			adj[city].emplace_back(n + i, ticket[i]);
			adj[n + i].emplace_back(city, 0);
		}
	}
 
	for(auto cost : dijkstra())
		cout << cost << ' ';
 
	cout << '\n';
 
	return 0;
}
