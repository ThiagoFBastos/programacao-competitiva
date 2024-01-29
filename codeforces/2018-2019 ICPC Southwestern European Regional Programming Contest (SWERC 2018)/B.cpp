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
struct SparseTable {
	vector<vector<T>> sp;
	int n, m;
	
	SparseTable() {}
	
	SparseTable(vector<T>& a) {
		n = a.size();
		m = 32 - __builtin_clz(n);
		
		sp = vector<vector<T>>(m, vector<T>(n));
		
		for(int i = 0; i < n; ++i) sp[0][i] = a[i];
		
		for(int i = 1; i < m; ++i)
		for(int j = 0; j + (1 << i) - 1 < n; ++j)
			sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
	}
	
	T query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return max(sp[k][l], sp[k][r - (1 << k) + 1]);
	}
};

int n;
SparseTable<int> L, R;

bool square(int x) {
	for(int i = 0; i <= n - x; ++i) {
		int lo = L.query(i, i + x - 1);
		int hi = -R.query(i, i + x - 1);
		if(hi - lo + 1 >= x) return true; 
	}
	return false;
}

void solve() {
	cin >> n;
	
	vector<int> l(n), r(n);
	
	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		l[i] = a;
		r[i] = -b;
	}
	
	L = SparseTable<int>(l);
	R = SparseTable<int>(r);
	
	int s = 0;
	
	for(int k = 31 - __builtin_clz(n); k >= 0; --k) {
		int side = s + (1 << k);
		if(square(side)) s = side;
	}
	
	cout << s << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


