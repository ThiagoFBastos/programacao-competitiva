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

const int N = 3e4 + 100;

vector<int> g[N];
int value[N], n, q, rnk[N], par[N];

int findSet(int u) {
	return u == par[u] ? u : par[u] = findSet(par[u]);
}

bool same(int u, int v) {
	return findSet(u) == findSet(v);
}

void join(int u, int v) {
	u = findSet(u), v = findSet(v);
	if(rnk[u] > rnk[v]) swap(u, v);
	par[u] = v;
	rnk[v] += rnk[u] == rnk[v];
}

struct HLD {
	int st[2 * N], sz[N], ptr[N], pos[N], h[N], par[N], id = 0;

	void dfs(int u, int p) {
		sz[u] = 1, par[u] = p;
		for(int v : g[u]) {
			if(v == p) continue;
			h[v] = 1 + h[u];
			dfs(v, u);
			sz[u] += sz[v];
		}
	}

	void get_paths(int u, int p) {
		for(int v : g[u]) {
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
	
	int rsq(int l, int r) {
		int sum = 0;
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) sum += st[l++];
			if(~r & 1) sum += st[r--];
		}
		return sum;
	}

	int query(int a, int b) {
		int ans = 0;
		while(ptr[a] != ptr[b]) {
			if(h[ptr[a]] > h[ptr[b]]) swap(a, b);
			ans += rsq(pos[b] - h[b] + h[ptr[b]], pos[b]);
			b = par[ptr[b]];
		}
		if(h[a] > h[b]) swap(a, b);
		return ans + rsq(pos[a], pos[b]);
	}

	void upd(int k, int x) {
		k = pos[k] + n;
		st[k] = x;
		for(k >>= 1; k; k >>= 1) st[k] = st[k << 1] + st[(k << 1) | 1];
	}

	HLD() {
		memset(ptr, -1, sizeof(int) * n);
		for(int i = 0; i < n; ++i) {
			if(ptr[i] < 0) {
				dfs(i, i);
				get_paths(i, i);
			}
			st[pos[i] + n] = value[i];
		}
		for(int i = n - 1; i; --i) st[i] = st[i << 1] + st[(i << 1) | 1];
	}
};

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> value[i];
		par[i] = i;
	}

	cin >> q;

	vector<tuple<int, int, int>> a(q);

	for(int i = 0; i < q; ++i) {
		string t;
		int x, y;
		cin >> t >> x >> y;
		if(t == "bridge") {
			--x, --y;
			a[i] = {0, x, y};
			if(!same(x, y)) {
				join(x, y);
				g[x].push_back(y);
				g[y].push_back(x);
			}
		} else if(t == "penguins") {
			--x;
			a[i] = {1, x, y};
		} else {
			--x, --y;
			a[i] = {2, x, y};
		}
	}

	memset(rnk, 0, n * sizeof(int));
	iota(par, par + n, 0);

	HLD hld;

	for(auto& v : a) {
		int t, x, y;
		tie(t, x, y) = v;
		if(t == 0) {
			if(same(x, y)) cout << "no\n";
			else {
				join(x, y);
				cout << "yes\n";
			}
		} else if(t == 1) hld.upd(x, y);
		else if(same(x, y)) cout << hld.query(x, y) << '\n';
		else cout << "impossible\n";
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