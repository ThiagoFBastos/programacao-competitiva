#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int MAXN = 2e5;
int n, q, tempo = 0, r = 0, p[MAXN], lv[MAXN], st[18][MAXN], prox[MAXN], root[MAXN], sink[MAXN], t[MAXN], low[MAXN], t_s[MAXN];
vi G[MAXN];
vvi scc;
stack<int> S;
void dfs(int v) {
	int u = prox[v];
	t[v] = low[v] = tempo++;
	S.push(v);
	if(t[u] == -1) {dfs(u); low[v] = min(low[v], low[u]);}
	else if(t_s[u] == -1) low[v] = t[u];
	if(t[v] == low[v]){
		int u;
		scc.push_back({});
		vi& g = scc.back();
		do {
			u = S.top();
			t_s[u] = scc.size() - 1;
			p[u] = g.size();
			g.push_back(u);
			S.pop();
		} while(u != v);
	}
}
void get_sink(int v){
	int u = prox[v];
	if(t_s[u] == t_s[v]) sink[v] = v;
	else {
		if(sink[u] == -1) get_sink(u);
		sink[v] = sink[u];
	}
}
void dfs(int v, int p, int h) {
	st[0][v] = p;
	lv[v] = h;
	root[v] = r;
	for(int u : G[v]) if(root[u] == -1) dfs(u, v, h + 1);
}
void solve() {
	for(int v = 0; v < n; ++v) --prox[v], t[v] = t_s[v] = sink[v] = root[v] = -1;
	for(int v = 0; v < n; ++v) if(t[v] == -1) dfs(v);
	for(int v = 0; v < n; ++v) if(sink[v] == -1) get_sink(v);
	int m = scc.size();
	for(int v = 0; v < n; ++v) {
		int u = prox[v];
		if(t_s[u] != t_s[v]) G[t_s[u]].push_back(t_s[v]);
	}
	for(int v = 0; v < n; ++v) {
		int u = t_s[v];
		if(sink[v] == v && root[u] == -1) {
			dfs(u, u, 0); 
			++r;
		}
	}
	int K = 31 - __builtin_clz(m);
	for(int i = 1; i <= K; ++i)
		for(int j = 0; j < m; ++j)
			st[i][j] = st[i - 1][st[i - 1][j]];
}
int lca(int u, int v) {
	int dist = lv[v] - lv[u], K = 31 - __builtin_clz(scc.size());
	for(int i = K; i >= 0; --i){
		if(dist >= (1 << i)){
			dist -= 1 << i;
			v = st[i][v];
		}
	}
	if(u != v) return -1;
	return v;
}
int distscc(int u, int v) {
	if(p[u] >= p[v]) return p[u] - p[v];
	return scc[t_s[u]].size() - p[v] + p[u];		
}
int dist(int u, int v) {
	if(t_s[u] == t_s[v]) return distscc(u, v);
	int U = t_s[u], V = t_s[v], w;
	if(lv[U] <= lv[V] || root[U] != root[V]) return -1;
	w = lca(V, U);
	if(w == -1) return -1;
	int x = sink[u];
	if(t_s[v] == t_s[x]) return lv[U] - lv[V] + distscc(x, v);
	return lv[U] - lv[V];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 0; i < n; ++i) cin >> prox[i];
	solve();
	while(q--) {
		int u, v;
		cin >> u >> v;
		cout << dist(u - 1, v - 1) << '\n';		
	}
	return 0;
}
