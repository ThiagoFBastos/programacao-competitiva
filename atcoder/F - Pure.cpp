#include "bits/stdc++.h"
using namespace std;
using ii = pair<int, int>;
void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<ii>> g(n), gr(n);
	vector<int> dist(n, -1), pai(n, -1);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back({b, i});
		gr[b].push_back({a, i});
	}
	auto p = make_tuple(n + 1, n, n);
	for(int v = 0; v < n; ++v) {
		for(auto [u, eu] : gr[v]) {
			queue<int> q;
			fill(dist.begin(), dist.end(), -1);
			dist[v] = 0;
			q.push(v);
			while(!q.empty()) {
				auto v = q.front();
				q.pop();
				for(auto [u, e] : g[v]) {
					if(e == eu || dist[u] != -1) continue;
					dist[u] = 1 + dist[v];
					q.push(u);
				}
			}
			if(dist[u] != -1) p = min(p, make_tuple(dist[u] + 1, v, u));
		}
	}
	if(get<0>(p) > n) {
		cout << "-1\n";
		return;
	}
	queue<int> q;
	auto [x, v, u] = p;
	pai[v] = v;
	q.push(v);
	while(!q.empty()) {
		auto v = q.front();
		q.pop();
		for(auto [u, e] : g[v]) {
			if(pai[u] != -1) continue;
			pai[u] = v;
			q.push(u);
		}
	}
	cout << x << '\n';
	stack<int> st;
	for(int v = u; v != pai[v]; v = pai[v]) st.push(1 + v);
	st.push(1 + v);
	while(!st.empty()) {
		cout << st.top() << '\n';
		st.pop();
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
