#pragma GCC optimize("O3")

#include "bits/stdc++.h"

using namespace std;

struct SegTree {
	vector<vector<int>> st;
	int r, c;
	
	SegTree() {}
	
	SegTree(int r, int c) {
		int n = 1 << (33 - __builtin_clz(r));
		int m = 1 << (33 - __builtin_clz(c));
		this->r = r;
		this->c = c;
		st = vector<vector<int>>(n, vector<int>(m, 0));
	}
	
	void upd_y(int j, int x, int lo, int hi, int nox, int no = 1) {
		if(lo == hi) st[nox][no] = x;
		else {
			int mid = (lo + hi) / 2;
			j <= mid ? upd_y(j, x, lo, mid, nox, 2 * no) : upd_y(j, x, mid + 1, hi, nox, 2 * no + 1);
			st[nox][no] = max(st[nox][2 * no], st[nox][2 * no + 1]);
		}
	}
	
	void upd_col(int j, int x, int lo, int hi, int nox, int no = 1) {
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			j <= mid ? upd_col(j, x, lo, mid, nox, 2 * no) : upd_col(j, x, mid + 1, hi, nox, 2 * no + 1);
		}
		st[nox][no] = max(st[2 * nox][no], st[2 * nox + 1][no]);
	}
	
	
	void upd_x(int i, int j, int x, int lo, int hi, int no = 1) {
		if(lo == hi) upd_y(j, x, 0, c - 1, no);
		else {
			int mid = (lo + hi) / 2;
			i <= mid ? upd_x(i, j, x, lo, mid, 2 * no) : upd_x(i, j, x, mid + 1, hi, 2 * no + 1);
			upd_col(j, x, 0, c - 1, no);
		}
	}
	
	int query_y(int y1, int y2, int lo, int hi, int nox, int no = 1) {
		if(y1 > y2) return 0;
		else if(y2 - y1 == hi - lo) return st[nox][no];
		int mid = (lo + hi) / 2;
		int L = query_y(y1, min(y2, mid), lo, mid, nox, 2 * no);
		int R = query_y(max(y1, mid + 1), y2, mid + 1, hi, nox, 2 * no + 1);
		return max(L, R);
	}
	
	int query_x(int x1, int x2, int y1, int y2, int lo, int hi, int no = 1) {
		if(x1 > x2) return 0;
		else if(x2 - x1 == hi - lo) return query_y(y1, y2, 0, c - 1, no);
		int mid = (lo + hi) / 2;
		int L = query_x(x1, min(x2, mid), y1, y2, lo, mid, 2 * no);
		int R = query_x(max(x1, mid + 1), x2, y1, y2, mid + 1, hi, 2 * no + 1);
		return max(L, R); 
	}
	
	void upd(int i, int j, int x) {
		upd_x(i, j, x, 0, r - 1);
	}
	
	int query(int x1, int y1, int x2, int y2) {
		return query_x(x1, x2, y1, y2, 0, r - 1);
	}
};

vector<vector<int>> g;
vector<int> x, y;
SegTree st;
int ans;

void dfs(int u) {
	
	int cnt = st.query(0, 0, x[u] - 1, y[u] - 1) + 1;
	
	ans = max(ans, cnt);
	
	st.upd(x[u], y[u], cnt);
	for(int v : g[u]) dfs(v);
	st.upd(x[u], y[u], 0);
}

void solve() {

	int n, m;
	cin >> n >> m;
	
	
	vector<bool> src(n, true);
	
	x.resize(n);
	y.resize(n);
	g.resize(n);
	
	for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
	
	auto px = x;
	auto py = y;
	
	sort(px.begin(), px.end());
	sort(py.begin(), py.end());
	
	px.resize(unique(px.begin(), px.end()) - px.begin());
	py.resize(unique(py.begin(), py.end()) - py.begin());

	for(int i = 0; i < n; ++i) {
		x[i] = lower_bound(px.begin(), px.end(), x[i]) - px.begin();
		y[i] = lower_bound(py.begin(), py.end(), y[i]) - py.begin();
	}
	
	st = SegTree(size(px), size(py));
	
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[b].push_back(a);
		src[a] = false;
	}
	
	for(int v = 0; v < n; ++v) {
		if(!src[v]) continue;
		dfs(v);
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}