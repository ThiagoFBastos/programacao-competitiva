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

vector<array<int, 2>> a;
int n, m;

struct SegTree {
	vector<array<array<bool, 2>, 2>> st;
	
	void create(int lo, int hi, int no = 1) {
		for(int i = 0; i < 2; ++i) st[no][i].fill(false);
		if(lo == hi) {
			st[no][0][0] = st[no][1][1] = true;
		} else {
			int mid = (lo + hi) / 2, L = 2 * no, R = 2 * no + 1;
			
			create(lo, mid, L);
			create(mid + 1, hi, R);
			
			for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
			for(int l = 0; l < 2; ++l)
				st[no][i][l] = st[no][i][l] || st[L][i][j] && st[R][k][l] 
				&& a[mid][j] <= a[mid + 1][k];
		}
	}
	
	void upd(int k, int x, int y, int lo, int hi, int no = 1) {
		if(lo != hi) {
			int mid = (lo + hi) / 2, L = 2 * no, R = 2 * no + 1;
			
			if(k <= mid) upd(k, x, y, lo, mid, L);
			else upd(k, x, y, mid + 1, hi, R);
			
			for(int i = 0; i < 2; ++i) st[no][i].fill(false);
			
			for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
			for(int l = 0; l < 2; ++l)
				st[no][i][l] = st[no][i][l] || st[L][i][j] && st[R][k][l] 
				&& a[mid][j] <= a[mid + 1][k];
				
		} else a[lo][0] = x, a[lo][1] = y;
	}
	
	SegTree() {
		int K = 1 << (33 - __builtin_clz(n));
		st.resize(K);
		create(0, n - 1);
	}
};

void solve() {	

	cin >> n;
	
	a.resize(n);
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < 2; ++j) cin >> a[i][j];
		if(a[i][0] > a[i][1]) swap(a[i][0], a[i][1]);
	}
	
	cin >> m;

	SegTree st;

	while(m--) {
		int x, y;
		bool flag = false;
		
		cin >> x >> y;
		
		--x, --y;
		
		int u[2] = {a[x][0], a[x][1]}, v[2] = {a[y][0], a[y][1]};
		
		st.upd(x, v[0], v[1], 0, n - 1);
		st.upd(y, u[0], u[1], 0, n - 1);
		
		for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			flag = flag || st.st[1][i][j];
		
		cout << (flag ? "TAK\n" : "NIE\n");
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
