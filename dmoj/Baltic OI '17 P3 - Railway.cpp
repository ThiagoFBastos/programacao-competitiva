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

const int N = 1e5 + 100, K = 17;

ii ed[N];
vector<ii> adj[N];
vector<int> out[N], ans;
set<int> sack[N];
int sp[K][N], depth[N], n, m, k;

void dfslca(int u, int p) {
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(auto [v, e] : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfslca(v, u);
	}
}

void dfsquery(int u, int p) {
	for(auto [v, e] : adj[u]) {
		if(v == p) continue;
		dfsquery(v, u);
		if((int)sack[v].size() >= k) ans.pb(e + 1);
		if(sack[u].size() < sack[v].size()) swap(sack[u], sack[v]);
		sack[u].insert(sack[v].begin(), sack[v].end());
	}
	for(int x : out[u]) sack[u].erase(x);
}

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) b = sp[i][b];
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(n); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

void solve() {
	cin >> n >> m >> k;

	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		ed[i] = {u, v};
		adj[u].pb({v, i});
		adj[v].pb({u, i});
	}

	dfslca(0, 0);

	for(int i = 0; i < m; ++i) {
		int s, u = -1;

		cin >> s;

		while(s--) {
			int v;
			cin >> v;
			--v;
			sack[v].insert(i);
			u = u != -1 ? lca(u, v) : v;
		}

		out[u].pb(i);
	}

	dfsquery(0, 0);

	sort(all(ans));

	cout << size(ans) << '\n';
	for(int e : ans) cout << e << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}

