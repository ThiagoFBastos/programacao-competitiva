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
	int n, q;
	cin >> n >> q;
	vector<int> x(n);
	vector<vector<int>> w(n), adj(n);
	for(int& v : x) cin >> v;
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	function<void(int, int)> dfs = [&](int u, int p) {
		w[u].push_back(x[u]);
		for(int v : adj[u]) {
			if(v == p) continue;
			dfs(v, u);
			for(int x : w[v]) w[u].push_back(x);
		}
		sort(w[u].rbegin(), w[u].rend());
		while(w[u].size() > 20) w[u].pop_back();
	};
	dfs(0, 0);
	while(q--) {
		int u, k;
		cin >> u >> k;
		--u, --k;
		cout << w[u][k] << '\n';
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
