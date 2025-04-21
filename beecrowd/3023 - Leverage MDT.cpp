#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

const int MAXN = 1 + 1e3;

int n, m, res = 0, p[MAXN][MAXN], c[MAXN][MAXN], LOG[MAXN];

char grid[MAXN][MAXN];

static int query(int x0, int y0, int x1, int y1);
static void solve(int x, int y);

int query(int x0, int y0, int x1, int y1) {
	return x1 - x0 + 1 + p[x1][y1] - p[x0 - 1][y1] - p[x1][y0 - 1] + p[x0 - 1][y0 - 1] - c[x1][y0] + c[x0 - 1][y0];
}

void solve(int x, int y) {
	int L = 1 + min(n - x, m - y);
	if(L <= res) return;
	int K = LOG[L], r = 0, s;
	s = 1 << K;
	for(int i = K; i >= 0; --i) {
		int z = r + s;
		if(z <= L && query(x, y, x + z - 1, y + z - 1) == z * z) r = z; 
		s >>= 1;
	}
	res = max(res, r);
}

int main() {
    LOG[1] = 0;
    for(int i = 2; i <= 1000; ++i) LOG[i] = 1 + LOG[i >> 1];
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= m; ++i) c[0][i] = p[0][i] = 0;
	for(int i = 0; i <= n; ++i) c[i][1] = p[i][0] = 0;
	for(int i = 1; i <= n; ++i) {
		getchar_unlocked();
		for(int k = 1; k <= m; ++k)
			grid[i][k] = getchar_unlocked();
	}
	for(int i = 1; i <= n; ++i) {
		for(int k = 2; k <= m; ++k) {
			if(grid[i][k] == grid[i][k - 1])
				p[i][k] = 1 + p[i - 1][k] + p[i][k - 1] - p[i - 1][k - 1];
			else
				p[i][k] = p[i - 1][k] + p[i][k - 1] - p[i - 1][k - 1];
		}
	}
	for(int k = 2; k <= m; ++k)
		for(int i = 1; i <= n; ++i)
			c[i][k] = c[i - 1][k] + (grid[i][k] == grid[i][k - 1]);
	for(int i = 1; i <= n; ++i)
		for(int k = 1; k <= m; ++k)
			solve(i, k);
	printf("%d\n", res * res);
	return 0;
}