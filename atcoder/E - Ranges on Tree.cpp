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
	int n, f = 1;

	cin >> n;
	vector<vector<int>> adj(n);

	vector<int> l(n), r(n);

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	function<void(int, int)> dfs = [&](int u, int p) {
		int c = (int)adj[u].size() - (u != p);
		if(c == 0) {
			l[u] = f, r[u] = f;
			++f;
		} else {
			l[u] = n + 1, r[u] = -1;
			for(int v : adj[u]) {
				if(v == p) continue;
				dfs(v, u);
				l[u] = min(l[u], l[v]);
				r[u] = max(r[u], r[v]);
			}
		}
	};	

	dfs(0, 0);
	
	for(int i = 0; i < n; ++i) cout << l[i] << ' ' << r[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
