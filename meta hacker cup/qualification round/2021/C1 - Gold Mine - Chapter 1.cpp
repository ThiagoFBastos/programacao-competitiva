#include "bits/stdc++.h"

using namespace std;

using ll = long long;

vector<int> c;
vector<vector<int>> g;
vector<ll> pre, max_pre;

int n;

void dfs(int u, int p) {
	pre[u] += c[u];
	max_pre[u] = pre[u];
	for(int v : g[u]) {
		if(v == p) continue;
		pre[v] = pre[u];
		dfs(v, u);
		max_pre[u] = max(max_pre[u], max_pre[v]);
	}
}

void solve() {
	cin >> n;
	
	c.resize(n);
	g.clear();
	g.resize(n);
	pre.assign(n, 0);
	max_pre.resize(n);
	
	for(int& v : c) cin >> v;
	
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	dfs(0, 0);
	
	ll ans = max_pre[0];
	
	if((int)g[0].size() > 1) {
		ll a, b;
		a = b = LLONG_MIN;
		for(int v : g[0]) {
			if(a < max_pre[v]) b = a, a = max_pre[v];
			else b = max(b, max_pre[v]);
		}
		ans = a + b - c[0];
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
 	return 0;
}
