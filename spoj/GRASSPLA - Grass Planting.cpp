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

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT() {}
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

const int N = 1e5 + 10;

int n, q;
vector<int> adj[N];

struct HLD {
	int sz[N], ptr[N], pos[N], h[N], par[N], id = 0;
	BIT<i64> bit;

	void dfs(int u, int p) {
		sz[u] = 1, par[u] = p;
		for(int v : adj[u]) {
			if(v == p) continue;
			h[v] = 1 + h[u];
			dfs(v, u);
			sz[u] += sz[v];
		}
	}

	void get_paths(int u, int p) {
		for(int v : adj[u]) {
			if(v == p) continue;
			get_paths(v, u);
		}
		if(ptr[u] != -1) return;
		stack<int> stk;
		while(true) {
			int v = par[u];
			stk.push(u);
			if(u == par[u] || sz[u] < (1 + sz[v]) / 2) break;
			u = v;
		}
		while(!stk.empty()) {
			int v = stk.top();
			stk.pop();
			pos[v] = id++, ptr[v] = u;
		}
	}
		
	i64 query(int a, int b) {
		return bit.query(pos[h[a] > h[b] ? a : b]);
	}

	void upd(int a, int b, int x) {
		while(ptr[a] != ptr[b]) {
			if(h[ptr[a]] > h[ptr[b]]) swap(a, b);
			int p = ptr[b];
			bit.upd(pos[b] - h[b] + h[p], x);
			bit.upd(pos[b] + 1, -x);
			b = par[p]; 
		}
		if(pos[a] > pos[b]) swap(a, b);
		bit.upd(pos[a] + 1, x);
		bit.upd(pos[b] + 1, -x);
	}

	HLD() {
		memset(ptr, -1, sizeof(int) * n);
		dfs(0, 0);
		get_paths(0, 0);
		bit = BIT<i64>(n);
	}
};

void solve() {
	cin >> n >> q;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HLD hld;
	while(q--) {
		char t;
		int u, v;
		cin >> t >> u >> v;
		--u, --v;
		if(t == 'P') hld.upd(u, v, 1);
		else cout << hld.query(u, v) << '\n';
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