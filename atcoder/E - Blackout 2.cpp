#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

int par[N], max_pos[N], cities[N], rnk[N], ans;
int n, m, e;

int findSet(int u) {
	return u == par[u] ? u : par[u] = findSet(par[u]);
}

void join(int u, int v) {
	

	u = findSet(u);
	v = findSet(v);
	
	if(u == v) return;

	if(rnk[u] > rnk[v]) swap(u, v);

	if(min(max_pos[u],max_pos[v]) < n && max(max_pos[u], max_pos[v]) >= n) {
		if(max_pos[u] < max_pos[v]) ans += cities[u];
		else ans += cities[v];
	}

	max_pos[v] = max(max_pos[v], max_pos[u]);
	cities[v] += cities[u];
	par[u] = v;
	rnk[v] += rnk[u] == rnk[v];
}

void solve() {

	cin >> n >> m >> e;

	vector<ii> ed(e);
	
	for(int i = 0; i < e; ++i) {
		int u, v;
		cin >> u >> v;
		ed[i] = {u-1,v-1};
	}

	for(int i = 0; i < n + m; ++i) {
		par[i] = i;
		cities[i] = i < n;
		max_pos[i] = i;
	}

	int q;

	cin >> q;

	vector<int> rt(q), X(q);
	vector<bool> use(e, true);

	for(int i = 0; i < q; ++i) {
		cin >> X[i];
		use[--X[i]] = false;
	}

	for(int i = 0; i < e; ++i) {
		auto [u, v] = ed[i];
		if(!use[i]) continue;
		join(u, v);
	}

	for(int i = q - 1; i >= 0; --i) {
		rt[i] = ans;	
		auto [u, v] = ed[X[i]];
		join(u, v);
	}

	for(int v : rt) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
