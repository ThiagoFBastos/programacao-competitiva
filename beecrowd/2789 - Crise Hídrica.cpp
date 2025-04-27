#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
const int maxn = 5e3;
vi T[maxn];
int n, m, q, d, lv[maxn], venda[maxn][2], st[13][maxn], litros[maxn], acumulo[maxn];
ll mochila[maxn];
void dfs(int v, int p) {
	st[0][v] = p;
	for(int u : T[v]) {
		if(u != p) {
			lv[u] = 1 + lv[v];
			dfs(u, v);
		}
	}
}
void passeio(int v, int p) {
	for(int u : T[v]) {
		if(u != p) {
			passeio(u, v);
			acumulo[v] += acumulo[u];
		}
	}
	litros[v] += acumulo[v];
}
int lca(int a, int b) {
	if(lv[a] > lv[b]) swap(a, b);
	int x = lv[b] - lv[a], R = 31 - __builtin_clz(n);
	for(int k = R; k >= 0; --k) {
		if(x >= (1 << k)) {
			x -= 1 << k;
			b = st[k][b];
		}
	}  
	if(a == b) return a;
	for(int k = R; k >= 0; --k) if(st[k][a] != st[k][b]) a = st[k][a], b = st[k][b];
	return st[0][a];
}
void lca_build() {
	int R = 31 - __builtin_clz(n);
	lv[0] = 0;
	dfs(0, 0);
	for(int k = 1; k <= R; ++k)	
		for(int i = 0; i < n; ++i)
			st[k][i] = st[k - 1][st[k - 1][i]];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> d;
	memset(acumulo, 0, sizeof(int) * n);
	memset(litros, 0, sizeof(int) * n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		T[a].push_back(b);
		T[b].push_back(a);
	}
	lca_build();
	cin >> m;
	for(int i = 0; i < m; ++i) {
		cin >> venda[i][0] >> venda[i][1];
		--venda[i][0];
	}
	cin >> q;
	while(q--) {
		int a, b, c, l;	
		cin >> a >> b >> l;
		--a, --b;
		c = lca(a, b);
		if(c == a) {
			acumulo[a] -= l;
			acumulo[b] += l;
			litros[a] += l;
		}
		else if(c == b) {
			acumulo[b] -= l;
			acumulo[a] += l;
			litros[b] += l;
		}
		else {
			acumulo[c] -= 2 * l;
			acumulo[a] += l;
			acumulo[b] += l;
			litros[c] += l;
		}
	}
	passeio(0, 0);
	for(int i = 0; i <= d; ++i) 
		mochila[i] = LLONG_MIN;
	mochila[0] = 0;
	for(int i = 0; i < m; ++i)
		for(int gasto = d - venda[i][1]; gasto >= 0; --gasto)
			mochila[gasto + venda[i][1]] = max(mochila[gasto + venda[i][1]], mochila[gasto] + litros[venda[i][0]]);
	ll ans = 0;
	for(int i = 0; i <= d; ++i) 
		ans = max(ans, mochila[i]);
	cout << ans << '\n';
 	return 0;
}