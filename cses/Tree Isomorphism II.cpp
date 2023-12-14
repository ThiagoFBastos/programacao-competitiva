#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
vector<int> C(vector<vector<int>>& g) {
	int n = size(g);
	vector<int> t(n), deg(n);
	queue<int> q;
	for(int u = 0; u < n; ++u) {
		deg[u] = size(g[u]);
		if(deg[u] <= 1) {
			t[u] = 0;
			q.push(u);
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : g[u]) {
			if(--deg[v] != 1) continue;
			t[v] = 1 + t[u];
			q.push(v);
		}
	}
	int maxt = *max_element(t.begin(), t.end());
	vector<int> c;
	for(int u = 0; u < n; ++u) if(maxt == t[u]) c.push_back(u);
	return c;
}
 
const int N = 1e5 + 100;
map<vector<int>, int> id;
vector<int> l[N];
 
int dfs(vector<vector<int>>& g, int u, int p) {
	for(int v : g[u]) {
		if(v == p) continue;
		l[u].push_back(dfs(g, v, u));
	}
	sort(l[u].begin(), l[u].end());
	if(!id.count(l[u])) return id[l[u]] = size(id);
	return id[l[u]];
}
 
void solve() {
	int n;
	cin >> n;
 
	vector<vector<int>> g[2];
 
	id.clear();
 
	for(int i = 0; i < 2; ++i) {
		g[i].resize(n);
		for(int j = 1; j < n; ++j) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			g[i][u].push_back(v);
			g[i][v].push_back(u);
		}
	}
 
	auto c = C(g[0]);
 
	for(int i = 0; i < n; ++i) l[i].clear();
	int x = dfs(g[0], c[0], c[0]);
 
	for(int v : C(g[1])) {
		for(int i = 0; i < n; ++i) l[i].clear();
		if(x == dfs(g[1], v, v)) {
			cout << "YES\n";
			return;
		}
	}
 
	cout << "NO\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
