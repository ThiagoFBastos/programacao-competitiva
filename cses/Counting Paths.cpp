#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 200000
vi T[MAXN];
int g[MAXN], p[MAXN], h[MAXN], in[MAXN], paths[MAXN], st[2 * MAXN][20], rmq[2 * MAXN], t_in = 0;
void dfs(int v, int hg = 0, int p = 0) {
	bool is_leaf {true};
	h[v] = hg;
	for(int u : T[v]) {
		if(u != p) {
			is_leaf = false;
			in[v] = t_in;
			rmq[t_in++] = v;
			dfs(u, hg + 1, v);
		}
	}
	if(is_leaf) {
		in[v] = t_in;
		rmq[t_in++] = v; 
	}
}
int lca(int u, int v) {
	int l = in[u], r = in[v], j, v1, v2;
	if(l > r) swap(l, r);
	j = log2(r - l + 1);
	v1 = st[l][j];
	v2 = st[r - (1 << j) + 1][j];
	return h[v1] < h[v2] ? v1 : v2;
}
void count_paths(int v, int parent = 0) {
	for(int u : T[v]) {
		if(u != parent) {
			count_paths(u, v);
			g[v] += g[u];
		}
	}
	paths[v] = g[v];
	g[v] -= p[v];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int v = 0; v < n; ++v)
		paths[v] = g[v] = p[v] = 0;
	for(int k = 1; k < n; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs(0);
	for(int k = 0; k < t_in; ++k)
		st[k][0] = rmq[k];
	int L = log2(t_in);
	for(int i = 1; i <= L; ++i) {
		for(int k = 0; k + (1 << i) - 1 < t_in; ++k) {
			int u = st[k][i - 1], v = st[k + (1 << i - 1)][i - 1];
			st[k][i] = h[u] < h[v] ? u : v;
		}
	}
	for(int k = 0; k < m; ++k) {
		int u, v, w;
		cin >> u >> v;
		--u, --v;
		w = lca(u, v);
		if(w == u) {
			++g[v];
			++p[u];
		}
		else if(w == v) {
			++g[u];
			++p[v];
		}
		else {
			++g[v];
			++g[u];
			--g[w];
			++p[w];
		}
	}
	count_paths(0);
	for(int i = 0; i < n; ++i) cout << paths[i] << ' ';
	cout << '\n';
    return 0;
}
