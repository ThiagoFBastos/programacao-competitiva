#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int MAXN = 1e5 + 1;
vi G[MAXN];
int st[18][MAXN], low[MAXN], t[MAXN], lv[MAXN], k = 0, n, m, q;
void dfs(int v, int p, int h) {
	low[v] = t[v] = k++;
	lv[v] = h;
	st[0][v] = p;
	for(int u : G[v]) {
		if(t[u] == -1) {
			dfs(u, v, h + 1);
			low[v] = min(low[u], low[v]);
		}
		else if(p != u) low[v] = min(low[v], t[u]);
	}
}
int up(int x, int v) {
	int L = 31 - __builtin_clz(n);
	for(int k = L; k >= 0; --k) {
		if((1 << k) <= x) {
			x -= 1 << k;
			v = st[k][v];
		}
	}
	return v;
}
int lca(int u, int v) {
	if(lv[u] > lv[v]) swap(u, v);
	v = up(lv[v] - lv[u], v);
	if(u == v) return v;
	int L = 31 - __builtin_clz(n);
	for(int k = L; k >= 0; --k) if(st[k][u] != st[k][v]) u = st[k][u], v = st[k][v];
	return st[0][u];
}
void solve() {
	memset(t, -1, sizeof(int) * n);
	dfs(0, 0, 0);
	int L = 31 - __builtin_clz(n);
	for(int k = 1; k <= L; ++k)	
		for(int i = 0; i < n; ++i)
			st[k][i] = st[k - 1][st[k - 1][i]];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q;	
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	solve();
	while(q--) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		if(a == c || b == c) cout << "NO\n";
		else {
			int d, e, f;
			d = lca(a, c);
			e = lca(b, c);
			f = lca(a, b);
			if((e == c || d == c) && !(d == e && d != f)) {
				if(e == c && d == c) {
					int p1, p2;
					p1 = up(lv[a] - lv[c] - 1, a);
					p2 = up(lv[b] - lv[c] - 1, b);
					if(max(low[p1], low[p2]) >= t[c]) cout << "NO\n";
					else cout << "YES\n";
				}
				else {
					int v = e == c ? b : a;
					int p = up(lv[v] - lv[c] - 1, v);
					if(low[p] >= t[c]) cout << "NO\n";
					else cout << "YES\n";
				}
			}
			else cout << "YES\n";
		}
	}
	return 0;
}
