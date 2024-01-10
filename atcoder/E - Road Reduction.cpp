#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, m;

	cin >> n >> m;

	vector<vector<tuple<int, int, int>>> g(n);
	vector<i64> cost(n, -1);
	priority_queue<pair<i64, int>> pq;

	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		g[a].emplace_back(b, c, i);
		g[b].emplace_back(a, c, i);
	}
	
	pq.emplace(0LL, 0);

	while(!pq.empty()) {
		auto [c, s] = pq.top();
		pq.pop();
		c *= -1;
		if(cost[s] != -1) continue;
		cost[s] = c;
		for(auto [t, d, k] : g[s]) {
			if(cost[t] != -1) continue;
			pq.emplace(-c - d, t);
		}
	}

	vector<int> ed;
	vector<bool> vis(n, false);
	queue<int> q;

	vis[0] = true;
	q.push(0);

	while(!q.empty()) {
		int s = q.front();
		q.pop();
		for(auto [t, d, k] : g[s]) {
			if(vis[t]) continue;
			if(cost[s] + d == cost[t]) {
				vis[t] = true;
				q.push(t);
				ed.push_back(k + 1);
			}
		}
	}

	for(int i = 0; i < (int)ed.size() - 1; ++i) cout << ed[i] << ' ';
	cout << ed.back() << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

