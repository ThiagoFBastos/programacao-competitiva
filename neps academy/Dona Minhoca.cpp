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

int n, diametro;
vector<vector<int>> g;
vector<int> d1, d2;

void preProcess(int u, int altura = 0, int p = -1) {
	d1[u] = d2[u] = 0;
	
	if(altura == diametro / 2) ++d1[u];
	if(altura == (1 + diametro) / 2) ++d2[u];
	
	for(int v : g[u]) {
		if(v == p) continue;
		preProcess(v, altura + 1, u);
		d1[u] += d1[v];
		d2[u] += d2[v];
	}
}

vector<int> centro(int& d) {
	queue<int> q;
	vector<int> deg(n), t(n), c;
	int T {};
	
	for(int v = 0; v < n; ++v) {
		deg[v] = g[v].size();
		if(deg[v] == 1) {
			t[v] = 0;
			q.push(v);
		}
	}
	
	while(!q.empty()) {
		int v = q.front();
		q.pop();		
		T = max(T, t[v]);
		for(int u : g[v]) {
			if(--deg[u] == 1) {
				t[u] = 1 + t[v];
				q.push(u);
			}
		}	
	}
	
	for(int v = 0; v < n; ++v) if(t[v] == T) c.push_back(v);
	d = 2 * T + (int)c.size() - 1;
	return c;
}

void solve() {
	cin >> n;
	
	g.resize(n);
	d1.resize(n);
	d2.resize(n);
	
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	auto c = centro(diametro);
	
	cout << 1 + diametro << '\n';
	
	preProcess(c[0]);
	
	i64 ans = 0, cnt = 0;
	
	for(int v : g[c[0]]) cnt += d1[v];
	
	if(diametro % 2 == 0) {
		for(int v : g[c[0]]) ans += d1[v] * (cnt - d1[v]);
		ans /= 2;
	} else {
		for(int v : g[c[0]]) ans += d2[v] * (cnt - d1[v]);
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}