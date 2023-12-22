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
	int n, m;

	cin >> n >> m;

	vector<vector<ii>> g(n);
	
	for(int i = 0; i < m; ++i) {
		int s, t;
		cin >> s >> t;
		--s, --t;
		g[s].emplace_back(t, i);
	}

	vector<int> dist(n, -1);
	vector<ii> p(n);
	queue<int> q;
	set<int> edges;

	dist[0] = 0;
	q.push(0);

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(auto [v, e] : g[u]) {
			if(dist[v] != -1) continue;
			p[v] = {u, e};
			dist[v] = 1 + dist[u];
			q.push(v);
		}
	}

	if(dist.back() >= 0) for(int u = n - 1; u; u = p[u].first) edges.insert(p[u].second);

	for(int i = 0; i < m; ++i) {
		if(edges.count(i)) {
			vector<int> d(n, -1);
			q.push(0);
			d[0] = 0;
			while(!q.empty()) {
				int u = q.front();
				q.pop();
				for(auto [v, e] : g[u]) {
					if(d[v] != -1 || e == i) continue;
					d[v] = 1 + d[u];
					q.push(v);
				}
			}
			cout << d.back() << '\n';
		} else cout << dist.back() << '\n';
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
