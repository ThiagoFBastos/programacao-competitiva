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

const int N = 1e5 + 100;

int cycle_pos[N], cycle_sz[N], last[N], deg[N], F[N], n, q, cycles;
queue<int> Q;

vector<int> adj[N];
int depth[N], sp[17][N];

void dfs(int u, int p) {
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : adj[u]) {
		depth[v] = 1 + depth[u];
		last[v] = last[u];
		cycle_pos[v] = cycle_pos[u];
		cycle_sz[v] = cycle_sz[u];
		dfs(v, u);
	}
}

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) b = sp[i][b];
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(depth[a]); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

void solve() {
	cin >> n;

	if(cin.eof()) exit(0);

	cycles = 0;

	for(int i = 0; i < n; ++i) {
		deg[i] = depth[i] = 0;
		cycle_pos[i] = -1;
		adj[i].clear();
	}

	for(int u = 0; u < n; ++u) {
		cin >> F[u];
		++deg[--F[u]];
	}

	for(int u = 0; u < n; ++u) if(!deg[u]) Q.push(u);

	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if(--deg[F[u]] == 0) Q.push(F[u]);
	}

	for(int v = 0; v < n; ++v) {
		if(!deg[v] || cycle_pos[v] != -1) continue;
		vector<int> C;
		for(int u = v, pos = 0; cycle_pos[u] == -1; u = F[u]) {
			cycle_pos[u] = pos++;
			last[u] = cycles;
			C.push_back(u);
		}
		for(int u : C) cycle_sz[u] = C.size();
		++cycles;
	}

	for(int u = 0; u < n; ++u) {
		if(deg[u]) continue;
		adj[F[u]].push_back(u);
	}

	for(int u = 0; u < n; ++u) if(deg[u]) dfs(u, u);
	
	cin >> q;

	while(q--) {
		int a, b;

		cin >> a >> b;

		--a, --b;		
	
		if(last[a] != last[b]) {
			cout << "-1\n";
			continue;
		} else if(cycle_pos[a] == cycle_pos[b]) {
			int c = lca(a, b);
			cout << depth[a] + depth[b] - 2 * depth[c] << '\n';
		} else {
			int diff = abs(cycle_pos[a] - cycle_pos[b]);
			cout << depth[a] + depth[b] + min(diff, cycle_sz[a] - diff) << '\n';
		}
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}