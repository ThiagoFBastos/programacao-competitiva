#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
using ii = pair<int, int>;
vector<int> deg;
vector<ii> max_deg, min_deg;
int l, n, m, a, b;
void create() {
	l = 1 << (32 - __builtin_clz(n));
	max_deg.resize(2 * l);
	min_deg.resize(2 * l);
	for(int k = l; k < n + l; ++k) {
		max_deg[k] = {deg[k - l], k - l};
		min_deg[k] = {deg[k - l], k - l};
	}
	for(int k = n + l; k < 2 * l; ++k) {
		max_deg[k] = {-INF, 0};
		min_deg[k] = {INF, 0};
	}
	for(int k = l - 1; k; --k) {
		max_deg[k] = max(max_deg[2 * k], max_deg[2 * k + 1]);
		min_deg[k] = min(min_deg[2 * k], min_deg[2 * k + 1]);
	}
}
void upd(int k, int x, int y) {
	k += l;
	max_deg[k].first = x;
	min_deg[k].first = y;
	for(k /= 2; k; k /= 2) {
		max_deg[k] = max(max_deg[2 * k], max_deg[2 * k + 1]);
		min_deg[k] = min(min_deg[2 * k], min_deg[2 * k + 1]);	
	}
}
void solve() {
	cin >> n >> m >> a >> b;
	vector<vector<int>> g(n);
	deg.assign(n, 0);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		++deg[u], ++deg[v];
		g[u].push_back(v);
		g[v].push_back(u);
	}
	create();
	while(n > 0) {
		int u = -1;
		if(min_deg[1].first < a) u = min_deg[1].second;
		else if(n - 1 - max_deg[1].first < b) u = max_deg[1].second;
		else break;
		deg[u] = -1;
		upd(u, -INF, INF);
		--n;
		for(int v : g[u]) {
			if(deg[v] < 0) continue;
			--deg[v];
			upd(v, deg[v], deg[v]); 
		}
	}
	cout << n << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}