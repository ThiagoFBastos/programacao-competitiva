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
	
	int n, u, v;

	cin >> n >> u >> v;

	--u, --v;

	vector<vector<int>> g(n);
	vector<int> du(n, 0), dv(n, 0);
	int ans = 0;

	for(int i = 1; i < n; ++i) {
		int u, v;	
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	function<void(vector<int>&, int u, int p)> dfs = [&](vector<int>& d, int u, int p) {
		for(int v : g[u]) {
			if(v == p) continue;
			d[v] = 1 + d[u];
			dfs(d, v, u);
		}
	};

	dfs(du, u, u);
	dfs(dv, v, v);

	for(int w = 0; w < n; ++w) {
		if(du[w] > dv[w]) continue;

		if(du[w] == dv[w]) {
			bool flag = false;
			for(int k : g[w]) flag = flag || du[k] == dv[k] && du[k] < du[w];
			if(flag) continue;
		}

		bool leaf = false;
		for(int k : g[w]) leaf = leaf || dv[w] < dv[k];
		if(leaf || du[w] == dv[w]) ans = max(ans, dv[w]);
		ans = max(ans, dv[w] - 1);
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
