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

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void solve() {
	int n, q;
	
	cin >> n;
	
	vector<vector<int>> g(n);
	vector<i64> pre(n, 0);
	vector<ii> edges;
	vector<int> h(n, 0);
	
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
		edges.emplace_back(a, b);
	}
	
	function<void(int, int)> level = [&](int u, int p) {
		for(int v : g[u]) {
			if(v == p) continue;
			h[v] = 1 + h[u];
			level(v, u);
		}
	};
	
	function<void(int, int)> dfs = [&](int u, int p) {
		for(int v : g[u]) {
			if(v == p) continue;
			pre[v] += pre[u];
			dfs(v, u);
		}
	};
	
	level(0, 0);
	
	cin >> q;
	
	while(q--) {
		int t, e, x;
		cin >> t >> e >> x;
		--e;
		if(t == 1) {
			auto [a, b] = edges[e];
			if(h[b] > h[a]) {
				pre[0] += x;
				pre[b] -= x;
			} else pre[a] += x;
		} else {
			auto [a, b] = edges[e];
			if(h[a] > h[b]) {
				pre[0] += x;
				pre[a] -= x;
			} else pre[b] += x;
		}
	}
	
	dfs(0, 0);
	
	for(i64 v : pre) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

