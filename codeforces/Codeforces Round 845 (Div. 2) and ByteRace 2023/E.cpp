#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
	int n, m;

	cin >> n >> m;

	vector<vector<int>> adj(n);
	vector<tuple<int, int, int>> ed(m);

	for(auto& [u, v, w] : ed) {
		cin >> u >> v >> w;
		--u, --v;
	}

	vector<int> low(n), t(n), scc(n), st, in(n);
	int nv, nscc;

	int l = 0, r = INF + 1;

	auto dfs = [&](auto& dfs, int u)->void {
		low[u] = t[u] = nv++;
		st.pb(u);
		for(int v : adj[u]) {
			if(t[v] == -1) {
				dfs(dfs, v);
				low[u] = min(low[u], low[v]);
			} else if(scc[v] == -1) low[u] = min(low[u], low[v]);
		}
		if(low[u] != t[u]) return;
		while(true) {
			int v = st.back(); st.pop_back();
			scc[v] = nscc;
			if(u == v) break;
		}		
		++nscc;
	};

	while(l < r) {
		int m = (l + r) / 2;

		for(int i = 0; i < n; ++i) {
			adj[i].clear();
			t[i] = scc[i] = -1;
			in[i] = 0;
		}

		nv = nscc = 0;

		for(auto [u, v, w] : ed) {
			if(w > m) adj[u].pb(v);
			else {
				adj[u].pb(v);
				adj[v].pb(u);
			}
		}

		for(int i = 0; i < n; ++i) {
			if(t[i] != -1) continue;
			dfs(dfs, i);
		}

		for(int i = 0; i < n; ++i) 
			for(int j : adj[i])
				in[scc[j]] += scc[i] != scc[j];

		if(count(in.begin(), in.begin() + nscc, 0) == 1) r = m;
		else l = m + 1;
	}

	if(r == INF + 1) r = -1;

	cout << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
