#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int N = 1e5 + 10;

int par[N], sz[N], depth[N];
int n, m, q, x[N], y[N], z[N], lo[N], hi[N];
ii edge[N];
vector<int> event[N];

int findSet(int u) {
	return u == par[u] ? u : par[u] = findSet(par[u]);
}

void join(int u, int v) {
	u = findSet(u);
	v = findSet(v);
	if(u == v) return;
	if(depth[u] > depth[v]) swap(u, v);
	par[u] = v, depth[v] += depth[u] == depth[v], sz[v] += sz[u];
}

void solve() {
	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		edge[i] = {a-1, b-1};
	}

	cin >> q;

	for(int i = 0; i < q; ++i) {
		cin >> x[i] >> y[i] >> z[i];
		--x[i], --y[i];
		lo[i] = 0, hi[i] = m - 1;
	}

	for(int k = m << 1; k; k >>= 1) {
		for(int i = 0; i < m; ++i) event[i].clear();
		for(int i = 0; i < n; ++i) par[i] = i, depth[i] = 0, sz[i] = 1;
		for(int i = 0; i < q; ++i) {
			if(lo[i] == hi[i]) continue;
			event[(lo[i] + hi[i]) / 2].pb(i);
		}
		for(int i = 0; i < m; ++i) {
			join(edge[i].fi, edge[i].sc);
			for(int j : event[i]) {
				int a = findSet(x[j]), b = findSet(y[j]);
				int e = a == b ? sz[a] : sz[a] + sz[b];
				if(e >= z[j]) hi[j] = i;
				else lo[j] = i + 1;
			}
		}
	}

	for(int i = 0; i < q; ++i) cout << 1 + hi[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
