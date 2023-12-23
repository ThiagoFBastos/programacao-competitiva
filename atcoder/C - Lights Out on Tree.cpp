#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 2e5 + 100;

vector<int> adj[N];
int in[N], out[N], depth[N], par[N], t, n, q;

void dfs(int u) {
	in[u] = t++;
	for(int v : adj[u]) {
		par[v] = u;
		depth[v] = 1 + depth[u];
		dfs(v);
	}
	out[u] = t - 1;
}

void solve() {
	cin >> n >> q;

	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		--p;
		adj[p].pb(i);
	}

	dfs(0);

	while(q--) {
		int m;
	
		cin >> m;
	
		vector<ii> a(m);
		set<ii> s;
		int ans = m;

		for(int i = 0; i < m; ++i) {
			int u;
			cin >> u;
			--u;
			a[i] = {depth[u], u};
		}

		sort(rall(a));

		for(auto [d, u] : a) {
			int deg = adj[u].size();

			auto it = s.lower_bound(ii(in[u], -1));

			while(it != s.end() && it->first <= out[u]) {
				auto [t, v] = *it;
				if(par[v] == u) --ans, --deg;
				it = s.erase(it); 
			}

			ans += deg;
			s.emplace(in[u], u);
		}

		cout << ans << '\n';
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
