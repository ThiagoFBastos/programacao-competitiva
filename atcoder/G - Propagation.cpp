#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n, m, q;

	cin >> n >> m >> q;

	vector<ii> c(n), upd(n);

	vector<vector<int>> adj(n), heavy(n);
	
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 0; i < n; ++i) {
		c[i] = upd[i] = {i + 1, 0};
		for(int j : adj[i]) {
			int deg = adj[j].size();
			if((i64)deg * deg >= m)
				heavy[i].push_back(j);
		}
	}

	for(int i = 1; i <= q; ++i) {
		int x;
		
		cin >> x;

		--x;

		int deg = adj[x].size();

		for(int y : heavy[x])
			if(upd[y].second > c[x].second)
				c[x] = upd[y];

		c[x].second = i;

		if((i64)deg * deg < m) {
			for(int y : adj[x]) c[y] = c[x];
		} else upd[x] = c[x];
	}

	for(int i = 0; i < n; ++i) {
		for(int y : heavy[i]) {
			if(upd[y].second > c[i].second)
				c[i] = upd[y];
		}
		cout << c[i].first << ' ';
	}

	cout << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

