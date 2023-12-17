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

const int N = 1001, inf = 1e9;

int pre[N][N];

struct SegTree {
	vector<vector<ii>> st;
	int r, c;
	
	SegTree() {}
	
	SegTree(int r, int c) {
		int n = 1 << (33 - __builtin_clz(r));
		int m = 1 << (33 - __builtin_clz(c));
		this->r = r;
		this->c = c;
		st = vector<vector<ii>>(n, vector<ii>(m, make_pair(inf, inf)));
	}
	
	void upd_y(int j, ii x, int lo, int hi, int nox, int no = 1) {
		if(lo == hi) st[nox][no] = x;
		else {
			int mid = (lo + hi) / 2;
			j <= mid ? upd_y(j, x, lo, mid, nox, 2 * no) : upd_y(j, x, mid + 1, hi, nox, 2 * no + 1);
			st[nox][no] = min(st[nox][2 * no], st[nox][2 * no + 1]);
		}
	}
	
	void upd_col(int j, ii x, int lo, int hi, int nox, int no = 1) {
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			j <= mid ? upd_col(j, x, lo, mid, nox, 2 * no) : upd_col(j, x, mid + 1, hi, nox, 2 * no + 1);
		}
		st[nox][no] = min(st[2 * nox][no], st[2 * nox + 1][no]);
	}
	
	
	void upd_x(int i, int j, ii x, int lo, int hi, int no = 1) {
		if(lo == hi) upd_y(j, x, 0, c - 1, no);
		else {
			int mid = (lo + hi) / 2;
			i <= mid ? upd_x(i, j, x, lo, mid, 2 * no) : upd_x(i, j, x, mid + 1, hi, 2 * no + 1);
			upd_col(j, x, 0, c - 1, no);
		}
	}
	
	ii query_y(int y1, int y2, int lo, int hi, int nox, int no = 1) {
		if(y1 > y2) return {inf, 0};
		else if(y2 - y1 == hi - lo) return st[nox][no];
		int mid = (lo + hi) / 2;
		ii L = query_y(y1, min(y2, mid), lo, mid, nox, 2 * no);
		ii R = query_y(max(y1, mid + 1), y2, mid + 1, hi, nox, 2 * no + 1);
		return min(L, R);
	}
	
	ii query_x(int x1, int x2, int y1, int y2, int lo, int hi, int no = 1) {
		if(x1 > x2) return {inf, 0};
		else if(x2 - x1 == hi - lo) return query_y(y1, y2, 0, c - 1, no);
		int mid = (lo + hi) / 2;
		ii L = query_x(x1, min(x2, mid), y1, y2, lo, mid, 2 * no);
		ii R = query_x(max(x1, mid + 1), x2, y1, y2, mid + 1, hi, 2 * no + 1);
		return min(L, R); 
	}
	
	void upd(int i, int j, ii x) {
		upd_x(i, j, x, 0, r - 1);
	}
	
	ii query(int x1, int y1, int x2, int y2) {
		return query_x(x1, x2, y1, y2, 0, r - 1);
	}
};

int query(int x0, int y0, int x1, int y1) {
	return pre[x1][y1] - pre[x0 - 1][y1] - pre[x1][y0 - 1] + pre[x0 - 1][y0 - 1];
}

void solve() {
	int n, m, a, b, c, d;
	
	cin >> m >> n >> b >> a >> d >> c;
	
	SegTree st(n + 1, m + 1);
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			cin >> pre[i][j];
			pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
		}
	}
	
	for(int i = 1; i + c - 1 <= n; ++i) {
		for(int j = 1; j + d - 1 <= m; ++j) {
			if(i + c - 1 <= n && j + d - 1 <= m) {
				ii x = {query(i, j, i + c - 1, j + d - 1), (i - 1) * m + j - 1};		
				st.upd(i, j, x);
			}
		}
	}
	
	auto ans = make_tuple(-inf, 0, 0);
	
	for(int i = 1; i + a - 1 <= n; ++i) {
		for(int j = 1; j + b - 1 <= m; ++j) {
			int p = i + 1, q = j + 1, r = i + a - 1 - c, s = j + b - 1 - d;
			ii x = st.query(p, q, r, s);
			ans = max(ans, make_tuple(query(i, j, i + a - 1, j + b - 1) - x.first, (i - 1) * m + j - 1, x.second));
		}
	}
	
	auto [p, q, r] = ans;
	
	int x0 = q / m + 1, y0 = q % m + 1;
	int x1 = r / m + 1, y1 = r % m + 1;
	
	cout << y0 << ' ' << x0 << '\n';
	cout << y1 << ' ' << x1 << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
