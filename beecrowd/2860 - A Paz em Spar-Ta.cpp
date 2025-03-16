#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int L = 17;
const int N = 1e5 + 100;

int lg(int x) {
	return x ? 31 - __builtin_clz(x) : 0;
}

unordered_map<int, int> pos[N];

vector<int> g[N], dt[N];
int depth[N], maxUp[N], maxDown[N], D[N][3];
int sp[L][N], lift[L][N];
int n, q;

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	for(int d = depth[b] - depth[a]; d; d -= d & -d) b = sp[__builtin_ctz(d)][b];
	if(a == b) return a;
	for(int i = lg(depth[a]); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

void dfs1(int u, int p) {
	maxDown[u] = 0;

	pos[u].reserve(size(g[u]));
	dt[u].resize(size(g[u]));
	memset(D[u], 0, sizeof D[u]);

	for(int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i];
		pos[u][v] = i;
		if(v == p) {
			dt[u][i] = 0;
			continue;
		}
		depth[v] = 1 + depth[u];
		dfs1(v, u);
		int d = maxDown[v] + 1;
		maxDown[u] = max(maxDown[u], d);
		if(D[u][0] < d) D[u][2] = D[u][1], D[u][1] = D[u][0], D[u][0] = d;
		else if(D[u][1] < d) D[u][2] = D[u][1], D[u][1] = d;
		else D[u][2] = max(D[u][2], d);
		dt[u][i] = d;
	}

	for(int v : g[u]) {
		if(v == p) continue;
		lift[0][v] = D[u][maxDown[v] + 1 == D[u][0]];
	}

	sp[0][u] = p;
}

void dfs2(int u, int p) {
	int D[2] = {0};
	for(int i = 1; (1 << i) < n; ++i) {
		sp[i][u] = sp[i - 1][sp[i - 1][u]];
		lift[i][u] = max(lift[i - 1][u], lift[i - 1][sp[i - 1][u]]);
	}
	for(int v : g[u]) {
		if(v == p) continue;
		int d = maxDown[v] + 1;
		if(D[0] < d) D[1] = D[0], D[0] = d;
		else D[1] = max(D[1], d);
	}
	for(int v : g[u]) {
		if(v == p) continue;	
		maxUp[v] = 1 + max(D[D[0] == maxDown[v] + 1], maxUp[u]);
		dfs2(v, u);
	}
}

int binary_lift(int& u, int d) {
	int val = 0;	
	if(d < 0) return 0;
	for(; d; d -= d & -d) {
		int i = __builtin_ctz(d);
		val = max(val, lift[i][u]);
		u = sp[i][u];
	}
	return val;
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		g[i].clear();
		pos[i].clear();
	}

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs1(0, 0);
	dfs2(0, 0);

	cin >> q;

	while(q--) {
		int i, j, k, d;
		cin >> i >> j;
		if(depth[i] > depth[j]) swap(i, j);
		k = lca(i, j);
		if(k == i) {
			d = max(maxDown[j], maxUp[i]);
			d = max(d, binary_lift(j, depth[j] - depth[i]));
		} else {
			d = max(maxDown[i], max(maxDown[j], maxUp[k]));
			d = max(d, binary_lift(i, depth[i] - depth[k] - 1));
			d = max(d, binary_lift(j, depth[j] - depth[k] - 1));

			int da = 1 + maxDown[i], db = 1 + maxDown[j];
			if(da < db) swap(da, db);

			if(da == D[k][0]) {
				if(db == D[k][1]) d = max(d, D[k][2]);
				else d = max(d, D[k][1]);
			} else d = max(d, D[k][0]);		
		}
		cout << d << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}