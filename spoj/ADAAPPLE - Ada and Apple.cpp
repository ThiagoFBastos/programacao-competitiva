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

const int N = 3e5 + 100, M = 1048576;
int n, q, tms, st[M], sz[N], pos[N], depth[N], par[N], x[N], head[N];
string type;
vector<int> adj[N];

struct HLD {

	void init(int lo, int hi, int no = 1) {
		if(lo == hi) st[no] = x[lo];
		else {
			int mid = (lo + hi) >> 1;
			init(lo, mid, no << 1);
			init(mid + 1, hi, (no << 1) | 1);
			st[no] = st[no << 1] + st[(no << 1) | 1];
		}
	}

	void upd(int k, int lo, int hi, int no = 1) {
		if(lo == hi) st[no] ^= 1;
		else {
			int mid = (lo + hi) >> 1;
			k <= mid ? upd(k, lo, mid, no << 1) : upd(k, mid + 1, hi, (no << 1) | 1);
			st[no] = st[no << 1] + st[(no << 1) | 1];
		}
	}

	int query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return 0;
		else if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) >> 1;
		int L = query(l, min(r, mid), lo, mid, no << 1);
		int R = query(max(l, mid + 1), r, mid + 1, hi, (no << 1) | 1);
		return L + R;
	}

	int query(int a, int b, int& lca) {
		int ans = 0;
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) swap(a, b);
			ans += query(pos[head[b]], pos[b], 0, n - 1);
			b = par[head[b]];
		}
		if(depth[a] > depth[b]) swap(a, b);
		lca = a;
		return ans + query(pos[a], pos[b], 0, n - 1);
	}

	void upd(int a) {
		upd(pos[a], 0, n - 1);	
	}

	void dfs(int u, int p) {
		sz[u] = 1, par[u] = p;
		if(!adj[u].empty() && adj[u][0] == p) swap(adj[u].back(), adj[u].front());
		for(int& v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfs(v, u);
			sz[u] += sz[v];
			if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
	}

	void get_paths(int u, int p) {
		pos[u] = tms++;
		for(int v : adj[u]) {
			if(v == p) continue;	
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			get_paths(v, u);
		}
	}
		
	HLD() {
		for(int i = 0; i < n; ++i) head[i] = i;
		dfs(0, 0);
		get_paths(0, 0);
		for(int i = 0; i < n; ++i) x[pos[i]] = type[i] - '0';
		init(0, n - 1);
	}
};


void solve() {
	cin >> n >> q >> type;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HLD hld;
	while(q--) {
		int t, i, j;
		cin >> t >> i;
		if(t == 0) hld.upd(i);
		else {
			int lca;
			cin >> j;
			int o = hld.query(i, j, lca);
			int nodes = depth[i] + depth[j] - 2 * depth[lca] + 1;
			cout << (o == nodes || !o ? "YES\n" : "NO\n");
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