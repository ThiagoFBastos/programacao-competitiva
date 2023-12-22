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

int n;
vector<vector<ii>> g;
vector<i64> pre, max_child, ans;
vector<int> d;

void getPre(int u, int p = -1) {
	max_child[u] = 0;
	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		pre[v] = w + pre[u];
		getPre(v, u);
		max_child[u] = max(max_child[u], max(pre[v] + d[v], max_child[v]));
	}
}

void dfs(int u, int p = -1, i64 lca = 0) {
	ans[u] = max(lca + pre[u], max_child[u] - pre[u]);
	i64 e1 = 0, e2 = 0;
	for(auto [v, w] : g[u]) {
		i64 c = max(pre[v] + d[v], max_child[v]);
		if(v == p) continue;
		else if(e1 < c) {
			e2 = e1;
			e1 = c;
		} else e2 = max(e2, c);
	}
	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		i64 c = max(pre[v] + d[v], max_child[v]);
		dfs(v, u, max(d[u] - pre[u], max(lca, (e1 == c ? e2 : e1) - 2 * pre[u])));
	}
}

void solve() {
	cin >> n;
	
	g.resize(n);
	d.resize(n);
	pre.resize(n);
	max_child.resize(n);
	ans.resize(n);
	
	for(int i = 1; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}	
	
	for(int& v : d) cin >> v;
	
	pre[0] = 0;
	getPre(0);
	dfs(0);
	
	for(i64 v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
