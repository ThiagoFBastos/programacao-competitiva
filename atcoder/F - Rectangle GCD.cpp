#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

struct op {
	int operator()(int a, int b) {
		return gcd(a, b);
	}
};

template<class T, class op>
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
			for(int j = 0; j + (1 << i) <= n; ++j)
				sp[i][j] = op()(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
	}
	
	T query(int l, int r) {
		if(l > r) return 0;
		int k = 31 - __builtin_clz(r - l + 1);
		return op()(sp[k][l], sp[k][r - (1 << k) + 1]);
	}
};

void solve() {
	int n, q;

	cin >> n >> q;

	vector<int> a(n), b(n);
	
	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	vector<int> A(n, 0), B(n, 0);

	for(int i = 0; i < n - 1; ++i) {
		A[i] = abs(a[i] - a[i + 1]);
		B[i] = abs(b[i] - b[i + 1]);
	}

	SparseTable<int, op> as(A), bs(B);

	while(q--) {
		int h1, h2, w1, w2;
		cin >> h1 >> h2 >> w1 >> w2;
		--h1, --h2, --w1, --w2;
		int g = a[h1] + b[w1];
		g = gcd(g, as.query(h1, h2 - 1));
		g = gcd(g, bs.query(w1, w2 - 1));
		cout << g << '\n';
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
