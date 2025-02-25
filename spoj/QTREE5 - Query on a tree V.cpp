#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e5 + 100, INF = 1e9;

set<ii> depths[N];
vector<int> g[N], his[N];
int n, q, sz[N], depth[N], lnk[N], c[N];
bool vis[N];

int findCentroid(int u, int p) {
	sz[u] = 1;
	for(int v : g[u]) {
		if(vis[v] || v == p) continue;
		(void)findCentroid(v, u);
		sz[u] += sz[v];
	}
	if(u == p) {
		int n = sz[u];
		while(true) {
			ii x(n - sz[u], p);
			for(int v : g[u]) {
				if(vis[v] || v == p) continue;
				x = max(x, ii(sz[v], v));
			}
			if(x.first <= n / 2) break;
			p = u, u = x.second;
		}
		return u;
	}
	return -1;
}

void dfs(int u, int p) {
	sz[u] = 1;
	his[u].push_back(depth[u]);
	for(int v : g[u]) {
		if(vis[v] || v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int centroid(int u) {
	int v = findCentroid(u, u);
	depth[v] = 0;
	dfs(v, v);
	vis[v] = true;
	for(int x : g[v]) {
		if(vis[x]) continue;
		lnk[centroid(x)] = v;
	}
	return v;
}

void upd(int v) {
	auto& h = his[v];
	int u = v;
	if(c[v]) {
		for(int i = (int)h.size() - 1; i >= 0; --i) {
			depths[v].erase(ii(h[i], u));	
			v = lnk[v];
		}
	} else {
		for(int i = (int)h.size() - 1; i >= 0; --i) {
			depths[v].insert(ii(h[i], u));	
			v = lnk[v];
		}
	}
	c[u] ^= 1;
}

int query(int v) {
	auto& h = his[v];
	if(c[v]) return 0;
	int ans = INF;
	for(int i = (int)h.size() - 1; i >= 0; --i) {
		auto& S = depths[v];
		if(!S.empty()) ans = min(ans, h[i] + S.begin()->first);
		v = lnk[v];
	}
	return ans;
}

void solve() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	(void)centroid(0);
	cin >> q;
	while(q--) {
		int t, v;
		cin >> t >> v;
		--v;
		if(t == 0) upd(v);
		else {
			int ans = query(v);
			cout << (ans == INF ? -1 : ans) << '\n';
		}
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