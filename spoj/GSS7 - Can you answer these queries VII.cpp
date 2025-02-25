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

struct node {
	int sum;
	int cnt;
	int pre;
	int suf;
	int best;
};

const int N = 1e5 + 10;

int n, q, id, x[N], sz[N], ptr[N], pos[N], h[N], par[N], lazy[4 * N];
vector<int> adj[N];
bool marked[4 * N];
node st[4 * N];

struct HLD {

	node merge(node& a, node& b) {
		node c;
		c.cnt = a.cnt + b.cnt;
		c.sum = a.sum + b.sum;
		c.pre = max(a.pre, a.sum + b.pre);
		c.suf = max(b.suf, b.sum + a.suf);
		c.best = max(max(a.best, b.best), a.suf + b.pre);
		return c;
	}

	void init(int lo, int hi, int no = 1) {
		if(lo == hi) {
			st[no].cnt = 1;
			st[no].sum = st[no].best = x[lo];
			st[no].pre = st[no].suf = max(0, x[lo]);
		} else {
			int mid = (lo + hi) >> 1;
			init(lo, mid, no << 1);
			init(mid + 1, hi, (no << 1) | 1);
			st[no] = merge(st[no << 1], st[(no << 1) | 1]);
		}
	}

	void push(node& a, int x) {
		a.sum = a.best = x * a.cnt; 
		a.pre = a.suf = max(0, a.sum);
	}

	void push(int no) {
		if(!marked[no]) return;
		int l = no << 1, r = (no << 1) | 1;
		push(st[l], lazy[no]);
		push(st[r], lazy[no]);
		lazy[l] = lazy[r] = lazy[no];
		marked[l] = marked[r] = true;
		marked[no] = false;
	}

	void upd(int l, int r, int x, int lo, int hi, int no = 1) {
		if(l > r) return;
		else if(r - l == hi - lo) {
			lazy[no] = x;
			marked[no] = true;
			push(st[no], x);
		} else {
			int mid = (lo + hi) >> 1;
			push(no);
			upd(l, min(r, mid), x, lo, mid, no << 1);
			upd(max(l, mid + 1), r, x, mid + 1, hi, (no << 1) | 1);
			st[no] = merge(st[no << 1], st[(no << 1) | 1]);	
		}
	}

	node query(int l, int r, int lo, int hi, int no = 1) {
		if(r - l == hi - lo) return st[no];
		int mid = (lo + hi) >> 1;
		push(no);
		if(l <= mid && r > mid) {
			node L = query(l, mid, lo, mid, no << 1);
			node R = query(mid + 1, r, mid + 1, hi, (no << 1) | 1); 
			return merge(L, R);
		} else if(r <= mid) return query(l, r, lo, mid, no << 1);
		return query(l, r, mid + 1, hi, (no << 1) | 1); 
	}

	i64 query(int a, int b) {
		int ans = 0, suf = 0, pre = 0;

		while(ptr[a] != ptr[b]) {
			int p;
			if(h[ptr[a]] > h[ptr[b]]) {
				p = ptr[a];
				int l = pos[a] - h[a] + h[p], r = pos[a];
				node y = query(l, r, 0, n - 1);
				ans = max(ans, max(y.best, suf + y.suf));
				suf = max(suf + y.sum, y.pre);
				a = par[p];
			} else {
				p = ptr[b];
				int l = pos[b] - h[b] + h[p], r = pos[b];
				node y = query(l, r, 0, n - 1);
				ans = max(ans, max(y.best, pre + y.suf));
				pre = max(pre + y.sum, y.pre);
				b = par[p]; 
			}
		}

		if(h[a] <= h[b]) {
			int l = pos[a], r = pos[b];
			node y = query(l, r, 0, n - 1);
			ans = max(ans, max(y.best, suf + y.pre));
			suf = max(suf + y.sum, y.suf);
		} else {
			int l = pos[b], r = pos[a];
			node y = query(l, r, 0, n - 1);
			ans = max(ans, max(y.best, suf + y.suf));
			suf = max(suf + y.sum, y.pre);
		}

		return max(ans, pre + suf);
	}

	void upd(int a, int b, int c) {
		while(ptr[a] != ptr[b]) {
			if(h[ptr[a]] > h[ptr[b]]) swap(a, b);
			int p = ptr[b];
			upd(pos[b] - h[b] + h[p], pos[b], c, 0, n - 1);
			b = par[p];
		}
		if(h[a] > h[b]) swap(a, b);
		upd(pos[a], pos[b], c, 0, n - 1);	
	}

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
		
	HLD() {
		memset(ptr, -1, sizeof(int) * n);
		dfs(0, 0);
		get_paths(0, 0);
		for(int i = 0; i < n; ++i) sz[pos[i]] = x[i];
		for(int i = 0; i < n; ++i) x[i] = sz[i];
		init(0, n - 1);
	}
};

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> x[i];
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cin >> q;
	HLD hld;
	while(q--) {
		int t, a, b, c;
		cin >> t >> a >> b;
		--a, --b;
		if(t == 1) cout << hld.query(a, b) << '\n';
		else {
			cin >> c;
			hld.upd(a, b, c);
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