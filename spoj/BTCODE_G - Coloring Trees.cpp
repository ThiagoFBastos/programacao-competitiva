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

const int N = 1e5 + 10;

vector<int> adj[N];
int sz[N], head[N], pa[N], pos[N], depth[N], st[2 * N], n, q, id;

struct HLD {
	
	void upd(int k, int x) {
		k = n + pos[k];
		st[k] = 1 << x;
		for(k /= 2; k; k /= 2) st[k] = st[2 * k] | st[2 * k + 1];
	}

	int query(int l, int r) {
		int ans = 0;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans |= st[l++];
			if(~r & 1) ans |= st[r--];
		}
		return ans;
	}

	int path(int a, int b) {
		int ans = 0;
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) swap(a, b);
			int c = head[b];
			ans |= query(pos[c], pos[b]);
			b = pa[c];
		}
		if(depth[a] > depth[b]) swap(a, b);
		return ans | query(pos[a], pos[b]);
	}

	void dfs(int u, int p) {
		sz[u] = 1, pa[u] = p;
		if(adj[u].front() == p) swap(adj[u].back(), adj[u].front());
		for(int& v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfs(v, u);
			sz[u] += sz[v];
			if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
	}

	void get_paths(int u, int p) {
		pos[u] = id++;
		for(int v : adj[u]) {
			if(v == p) continue;	
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			get_paths(v, u);
		}
	}
		
	HLD() {
		iota(head, head + n, 0);
		fill(st, st + 2 * n + 1, 1);
		dfs(0, 0);
		get_paths(0, 0);
	}
};

void solve() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	cin >> q;
	HLD hld;
	while(q--) {
		int t, a, b;
		cin >> t >> a >> b;
		if(t == 1) hld.upd(a, b);
		else {
			int ans = hld.path(a, b);
			if(ans % 2 || __builtin_popcount(ans) != 1) cout << "NO\n";
			else cout << "YES\n";
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