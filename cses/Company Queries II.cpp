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
int rqm[2 * MAXN], pos[MAXN], h[MAXN], k = 0;
vi G[MAXN];
void dfs(int v, int hg = 0) {
	bool is_leaf {true};
	h[v] = hg;
	for(int w : G[v]) {
		if(h[w] == -1) {
			is_leaf = false;
			pos[v] = k;
			rqm[k++] = v;
			dfs(w, hg + 1);
		}
	}
	if(is_leaf) {
		pos[v] = k;
		rqm[k++] = v;
	}
}
int st[2 * MAXN][20], LOG[2 * MAXN];
inline int lca(int u, int v) {
	int pu = pos[u], pv = pos[v];
	if(pu > pv) swap(pv, pu);
	int L = LOG[pv - pu + 1];
	int U = st[pu][L], V = st[pv - (1 << L) + 1][L];
	return h[U] < h[V] ? U : V;	
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	memset(h, -1, n * sizeof(int));
	for(int k = 1; k < n; ++k) {
		int boss;
		cin >> boss;
		G[boss - 1].push_back(k);
	}
	dfs(0);
	for(int v = 0; v < k; ++v)
		st[v][0] = rqm[v];
	LOG[1] = 0;
	for(int i = 2; i <= k; ++i)
		LOG[i] = 1 + LOG[i >> 1];
	int N = LOG[k];
	for(int i = 1; i <= N; ++i) {
		for(int j = 0; j + (1 << i) - 1 < k; ++j) {
			int u = st[j][i - 1], v = st[j + (1 << i - 1)][i - 1];
			st[j][i] = h[u] < h[v] ? u : v;
		}
	}
	while(q--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		cout << 1 + lca(u, v) << '\n';
	}
    return 0;
}
 
