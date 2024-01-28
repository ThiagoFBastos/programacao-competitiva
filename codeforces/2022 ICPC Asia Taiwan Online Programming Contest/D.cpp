#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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
		return min(a, b);
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
		if(l > r) return INF;
		int k = 31 - __builtin_clz(r - l + 1);
		return op()(sp[k][l], sp[k][r - (1 << k) + 1]);
	}
};

void solve() {
	int n;

	cin >> n;

	vector<int> d(n), p(n, -1);
	vector<vector<int>> st(n);

	for(int i = 0; i < n; ++i) {
		cin >> d[i];
		st[d[i]].pb(i);
	}

	if(count(all(d), 0) != 1) {
		cout << "-1\n";
		return;
	}

	SparseTable<int, op> sp(d);

	auto nxt = [&](int x, int i) {
		if(st[x].empty()) return -1;
		else if(st[x].back() >= i) return *lower_bound(all(st[x]), i);
		return st[x][0];
	};

	auto prv = [&](int x, int i) {
		if(st[x].empty()) return -1;
		else if(st[x][0] <= i) return *prev(lower_bound(all(st[x]), i));
		return st[x].back();
	};

	auto test = [&](int i, int j, int x) {
		if(i > j) swap(i, j);
		return sp.query(i + 1, j - 1) > x ||
		min(sp.query(0, i - 1), sp.query(j + 1, n - 1)) > x;
	};

	for(int i = 0; i < n; ++i) {
		if(!d[i]) continue;
		int j = prv(d[i] - 1, i);	
		if(j != -1 && test(i, j, d[i] - 1)) {p[i] = j; continue;}
		j = nxt(d[i] - 1, i);
		if(j != -1 && test(i, j, d[i] - 1)) {p[i] = j; continue;}
		cout << "-1\n";
		return;
	}

	for(int i = 0; i < n; ++i) if(p[i] != -1) cout << i + 1 << ' ' << p[i] + 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

