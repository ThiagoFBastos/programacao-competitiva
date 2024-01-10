#include "bits/stdc++.h"

#define endl '\n'

using namespace std;

int n;
vector<vector<int>> g;
vector<int> c, v;
map<int, int> s;

void dfs(int u, int p) {
	if(!s.count(c[u])) v.push_back(u + 1);
	++s[c[u]];
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
	}
	if(--s[c[u]] == 0) s.erase(c[u]);
}

void solve() {
	cin >> n;
	g.resize(n);
	c.resize(n);
	
	for(int& v : c) cin >> v;
	
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	dfs(0, 0);
	
	sort(v.begin(), v.end());
	for(int x : v) cout << x << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}

