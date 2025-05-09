#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
const int maxn = 501;
int n, p, grid[maxn][maxn], pr[maxn][maxn][2], K;
int query(int x, int y, int a, int k) {
	return pr[x + a - 1][y + a - 1][k] - pr[x - 1][y + a - 1][k] - pr[x + a - 1][y - 1][k] + pr[x - 1][y - 1][k];
}
int solve(int x, int y, int k) {
	int a = 0, b = 0, l = 1 + n - max(x, y);
	for(int i = K; i >= 0; --i) {
		int z = 1 << i;
		if(a + z <= l && !query(x, y, a + z, k ^ 1)) a |= z;
		if(b + z <= l && !query(x, y, b + z, k)) b |= z;
	}
	return a && query(x, y, a, k) ? a - b : 0;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> p;
	K = 31 - __builtin_clz(n);
	for(int i = 0; i <= n; ++i) {
		for(int k = 0; k <= n; ++k) {
			grid[i][k] = -1;
			pr[i][k][0] = pr[i][k][1] = 0;
		}
	}
	for(int i = 0; i < p; ++i) {
		int r, c;	
		cin >> r >> c;
		grid[r][c] = 0;
	}
	for(int i = 0; i < p; ++i) {
		int r, c;	
		cin >> r >> c;
		grid[r][c] = 1;
	}
	for(int i = 1; i <= n; ++i)
		for(int k = 1; k <= n; ++k)
			for(int j = 0; j < 2; ++j)
				pr[i][k][j] = (grid[i][k] == j) + pr[i][k - 1][j] + pr[i - 1][k][j] - pr[i - 1][k - 1][j];
	ll W = 0, B = 0;
	for(int i = 1; i <= n; ++i) {
		for(int k = 1; k <= n; ++k) {
			B += solve(i, k, 0);
			W += solve(i, k, 1);
		}
	}
	cout << B << ' ' << W << '\n';
	return 0;
}