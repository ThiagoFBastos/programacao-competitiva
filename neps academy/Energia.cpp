#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9 + 1;
vector<int> t, pai, ranking, label;
vector<vector<int>> L, pre;
int find_set(int v) {
	return v == pai[v] ? v : find_set(pai[v]);
}
void join(int u, int v, int w) {
	u = find_set(u), v = find_set(v);
	if(u == v) return;
	if(ranking[u] > ranking[v]) swap(u, v);
	ranking[v] += ranking[u] == ranking[v];
	pai[u] = v;
	label[u] = w;
	t[v] += t[u];
	L[v].push_back(w);
	pre[v].push_back(pre[v].back() + t[u]);
}
void create(int n) {
	t.resize(n);
	pai.resize(n);
	ranking.assign(n, 1);
	label.assign(n, INF);
	L.resize(n);
	pre.resize(n);
	for(int i = 0; i < n; ++i) {
		pai[i] = i;
		L[i].push_back(0);
	}
}
void solve() {
	int n, m, q;
	cin >> n >> m;
	create(n);
	for(int i = 0; i < n; ++i) {
		cin >> t[i];
		pre[i].push_back(t[i]);
	}
	vector<tuple<int, int, int>> edges(m);
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[i] = {w, u - 1, v - 1};
	}
	sort(edges.begin(), edges.end());
	for(auto& aresta : edges) join(get<1>(aresta), get<2>(aresta), get<0>(aresta));
	cin >> q;
	int ans = 0;
	while(q--) {
		int u, k;
		cin >> u >> k;
		--u, k += ans;
		while(label[u] <= k) u = pai[u];	
		int j = upper_bound(L[u].begin(), L[u].end(), k) - L[u].begin() - 1;
		cout << pre[u][j] << '\n';
		ans = pre[u][j];
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}