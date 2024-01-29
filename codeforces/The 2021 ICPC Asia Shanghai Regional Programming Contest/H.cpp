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

int n, m, q;

vector<int> r, p;
vector<i64> cost;
vector<set<ii>> dsu;

int findSet(int u) {
	return p[u] == u ? u : p[u] = findSet(p[u]);
}

bool same(int u, int v) {
	return findSet(u) == findSet(v);
}

void join(int u, int v) {
	if(r[u] > r[v]) swap(u, v);
	if(dsu[u].size() > dsu[v].size()) swap(dsu[u], dsu[v]);
	for(auto& x : dsu[u]) dsu[v].insert(x);
	p[u] = v;
	r[v] += r[u] == r[v];
	cost[v] += cost[u];
}

void solve() {

	cin >> n >> m >> q;

	vector<int> a(n);
	vector<tuple<int, int, int>> e(m);
	vector<i64> ans(q, 0);

	for(int& v : a) cin >> v;	

	for(int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		e[i] = {w, u - 1, v - 1};
	}

	sort(e.begin(), e.end());

	p.resize(n);
	r.resize(n);
	dsu.resize(n);
	cost.resize(n);

	for(int i = 0; i < n; ++i) {
		p[i] = i;
		r[i] = 0;
		cost[i] = a[i];
	}

	for(int i = 0; i < q; ++i) {
		int x, k;
		cin >> x >> k;
		ans[i] = k;
		dsu[x - 1].insert(ii(k, i));
	}

	for(auto [w, u, v] : e) {
		if(same(u, v)) continue;

		u = findSet(u);

		while(!dsu[u].empty()) {
			auto [x, k] = *dsu[u].begin();
			if(x + cost[u] >= w) break;
			dsu[u].erase(dsu[u].begin());
			ans[k] += cost[u];
		}

		v = findSet(v);

		while(!dsu[v].empty()) {
			auto [x, k] = *dsu[v].begin();
			if(x + cost[v] >= w) break;
			dsu[v].erase(dsu[v].begin());
			ans[k] += cost[v];
		}

		join(u, v);
	}
	
	int v = findSet(0);
	for(auto [x, k] : dsu[v]) ans[k] += cost[v];

	for(i64 c : ans) cout << c << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

