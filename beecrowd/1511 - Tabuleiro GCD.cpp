#pragma GCC optimize("O3", "Ofast", "unroll-loops")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4", "avx")

#include "bits/stdc++.h"

using namespace std;

using ii = pair<int, int>;

struct SegTree {
	vector<vector<int>> st;
	int r, c;
	
	SegTree(int r, int c) {
		this->r = r;
		this->c = c;
		st = vector<vector<int>>(2 * r + 1, vector<int>(2 * c + 1, 0));
	}
	
	void upd_col(int i, int j, int x) {
		for(j += c; j; j >>= 1) st[i][j] = gcd(st[i << 1][j], st[(i << 1) | 1][j]);
	}
	
	void upd_bottom(int i, int j, int x) {
		j += c;
		st[i][j] = x;
		for(j >>= 1; j; j >>= 1) st[i][j] = gcd(st[i][j << 1], st[i][(j << 1) | 1]);
	}
	
	void upd_row(int i, int j, int x) {
		i += r;
		upd_bottom(i, j, x);
		for(i >>= 1; i; i >>= 1) upd_col(i, j, x);
	}
	
	int query_y(int x, int l, int r) {
		int g = 0;
		for(l += c, r += c; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) g = gcd(g, st[x][l++]);
			if(~r & 1) g = gcd(g, st[x][r--]);
		}
		return g;
	}
	
	int query_x(int x1, int x2, int y1, int y2) {
		int g = 0;
		for(x1 += r, x2 += r; x1 <= x2; x1 >>= 1, x2 >>= 1) {
			if(x1 & 1) g = gcd(g, query_y(x1++, y1, y2));
			if(~x2 & 1) g = gcd(g, query_y(x2--, y1, y2));
		}
		return g;
	}
};

void solve() {
	int q;
	
	cin >> q;
	
	if(cin.eof()) exit(0);
	
	vector<tuple<int, int, int, int>> a(q);
	vector<int> X(q), Y(q);
	
	for(int i = 0; i < q; ++i) {
		string t;
		int x, y, d;
		cin >> t >> x >> y >> d;
		x += y; y = x - 2 * y;
		X[i] = x, Y[i] = y;
		a[i] = make_tuple(t != "SET", x, y, d);
	}
	
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	
	SegTree st(size(X), size(Y));
	
	for(auto [t, x, y, d] : a) {
		if(t == 0) {
			int _x = lower_bound(X.begin(), X.end(), x) - X.begin();
			int _y = lower_bound(Y.begin(), Y.end(), y) - Y.begin();
			st.upd_row(_x, _y, d);
		} else {
		
			int x1 = lower_bound(X.begin(), X.end(), x - d) - X.begin();
			int x2 = upper_bound(X.begin(), X.end(), x + d) - X.begin() - 1;
			
			int y1 = lower_bound(Y.begin(), Y.end(), y - d) - Y.begin();
			int y2 = upper_bound(Y.begin(), Y.end(), y + d) - Y.begin() - 1;
			
			cout << st.query_x(x1, x2, y1, y2) << '\n';
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	while(1) solve();
	return 0;
}