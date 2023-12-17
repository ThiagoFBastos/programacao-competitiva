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

const int N = 1e5;

int n, e, q, tms, sp[17][N];
vector<int> lo, t, h;
vector<vector<int>> g;

void dfs(int u, int p) {
	lo[u] = t[u] = tms++;
	sp[0][u] = p;
	for(int v : g[u]) {
		if(lo[v] < 0) {
			h[v] = 1 + h[u];
			dfs(v, u);
			lo[u] = min(lo[u], lo[v]);
		} else if(v != p) lo[u] = min(lo[u], t[v]);
	}
}

int up(int u, int d) {
	for(int k = 31 - __builtin_clz(d + 1); k >= 0; --k) {
		if(d < (1 << k)) continue;
		d -= 1 << k;
		u = sp[k][u];
	}
	return u;
}

int lca(int u, int v) {
	if(h[u] > h[v]) swap(u, v);
	v = up(v, h[v] - h[u]);
	if(u == v) return u;
	for(int k = 31 - __builtin_clz(n); k >= 0; --k) {
		if(sp[k][v] == sp[k][u]) continue;		
		v = sp[k][v], u = sp[k][u];
	}
	return sp[0][v];
}

bool in_path(int a, int b, int c) {
	int d = lca(a, b);	
	return lca(c, d) == d && (lca(a, c) == c || lca(b, c) == c);
}

void solve() {
	cin >> n >> e;

	g.resize(n);
	lo.assign(n, -1);
	t.resize(n);
	h.resize(n);
	
	for(int i = 0; i < e; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}

	h[0] = 0;
	dfs(0, 0);
	
	int lg = 32 - __builtin_clz(n);

	for(int i = 1; i < lg; ++i)
	for(int j = 0; j < n; ++j)
		sp[i][j] = sp[i - 1][sp[i - 1][j]];

	cin >> q;

	while(q--) {
		int tp, a, b, c;

		cin >> tp >> a >> b;

		--a, --b;

		if(tp == 1) {
			int g1, g2;

			cin >> g1 >> g2;

			--g1, --g2;

			if(h[g1] > h[g2]) swap(g1, g2);
		
			if(in_path(a, b, g1) && in_path(a, b, g2)) {
				if(lo[g2] > t[g1]) cout << "no\n";
				else cout << "yes\n";
			} else cout << "yes\n";

		} else {
			cin >> c;

			--c;

			if(!in_path(a, b, c)) {
				cout << "yes\n";
				continue;
			} else if(a == c || b == c) {
				cout << "no\n";
				continue;
			}

			int d = lca(a, b);

			if((in_path(a, d, c) && lo[up(a, h[a] - h[c] - 1)] >= t[c]) || (in_path(b, d, c) && lo[up(b, h[b] - h[c] - 1)] >= t[c])) {
				cout << "no\n";
				continue;
			}

			cout << "yes\n";
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
