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
vi G[MAXN];
int h[MAXN], st[4 * MAXN], rmq[2 * MAXN], p[MAXN], k = 0;
void dfs(int v, int hg) {
	bool is_leaf {true};
	h[v] = hg;
	for(int u : G[v]) {
		if(h[u] == -1) {
			is_leaf = false;
			p[v] = k;
			rmq[k++] = v;
			dfs(u, hg + 1);
		}
	}
	if(is_leaf) {
		p[v] = k;
		rmq[k++] = v;
	}
}
int lca_h(int u, int w) {
	int H = INT_MAX, l = p[u] + k, r = p[w] + k;
	if(l > r) swap(l, r);
	while(l <= r) {
		if(l & 1) H = min(H, st[l++]);
		if(!(r & 1)) H = min(H, st[r--]);
		l >>= 1;
		r >>= 1;
	}
	return H;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	memset(h, -1, sizeof(int) * n);
	for(int k = 1; k < n; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(0, 0);
	for(int i = 2 * k - 1; i >= k; --i)
		st[i] = h[rmq[i - k]];
	for(int i = k - 1; i > 0; --i)
		st[i] = min(st[i << 1], st[(i << 1) | 1]);
	while(q--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		cout << h[u] + h[v] - 2 * lca_h(u, v) << '\n';
	}
    return 0;
}
