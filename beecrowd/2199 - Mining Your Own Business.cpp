#include "bits/stdc++.h"
using namespace std;
vector<vector<int>> g;
vector<int> id, cnt_id, lo, t, j;
int n, tms;
void dfs(int u) {
	int cnt = 0;
	bool flag = false;
	lo[u] = t[u] = tms++;
	for(int v : g[u]) {
		if(t[v] == -1) {
			++cnt;
			dfs(v);
			if(u) {
				if(lo[v] >= t[u]) flag = true;
				lo[u] = min(lo[u], lo[v]);
			}
		} else lo[u] = min(lo[u], t[v]);
	}
	if(!u && cnt > 1) flag = true;
	if(flag) j.push_back(u);
}
void mark(int u, int x) {
	id[u] = x;
	++cnt_id[x];
	for(int v : g[u]) {
		if(id[v] != -1) continue;
		mark(v, x);
	}
}
void solve(int kase) {
	cin >> n;
	if(!n) exit(0);
	vector<int> v;
	vector<pair<int, int>> e(n);
	int w = 0, x = 0;
	long long y = 1;
	for(int i = 0; i < n; ++i) {
		int s, t;
		cin >> s >> t;
		e[i] = {s, t};
		v.push_back(s);
		v.push_back(t);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	n = size(v);
	g.clear();
	j.clear();
	g.resize(n);
	t.assign(n, -1);
	id.assign(n, -1);
	lo.resize(n);
	cnt_id.assign(n, 0);
	tms = 0;
	for(auto [s, t] : e) {
		s = lower_bound(v.begin(), v.end(), s) - v.begin();
		t = lower_bound(v.begin(), v.end(), t) - v.begin();
		g[s].push_back(t);
		g[t].push_back(s);
	}
	dfs(0);
	for(int v : j) {
		cnt_id[w] = 1;
		id[v] = w++;
	}
	for(int v = 0; v < n; ++v) {
		if(id[v] != -1) continue;
		mark(v, w);
		++w; 
	}
	vector<int> deg(w, 0);
	set<pair<int, int>> aresta;
	for(int v = 0; v < n; ++v) {
		for(int u : g[v]) {
			if(id[u] == id[v]) continue;
			aresta.insert({min(id[u], id[v]), max(id[u], id[v])});
		}
	}
	for(auto [u, v] : aresta) ++deg[u], ++deg[v];
	for(int v = 0; v < w; ++v) {
		if(deg[v] == 1) {
			++x;
			y *= cnt_id[v];
		} else if(deg[v] == 0) {
			x += 2;
			y = cnt_id[v] * (cnt_id[v] - 1LL) / 2;
		}
	}
	cout << "Case " << kase << ": " << x << ' ' << y << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(int t = 1; ; ++t) solve(t);
	return 0;
}