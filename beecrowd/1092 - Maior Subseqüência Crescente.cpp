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
const int maxn = 600;
int st[9][maxn], a[maxn][maxn], f[maxn][maxn], b[maxn][maxn], nxt[maxn][maxn], n, m;
static int query(int l, int r);
int query(int l, int r) {
	int K = 31 - __builtin_clz(r - l + 1);
	return min(st[K][l], st[K][r - (1 << K) + 1]);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		int res = 1;
		cin >> n >> m;
		if(!(n || m)) break;
		for(int i = 0; i < n; ++i)
		for(int k = 0; k < m; ++k)
			cin >> a[i][k];
		for(int i = 0; i < n; ++i) {
			b[i][0] = 1;
			for(int k = 1; k < m; ++k) {
				if(a[i][k] > a[i][k - 1]) b[i][k] = 1 + b[i][k - 1];
				else b[i][k] = 1;
				res = max(res, b[i][k]);
			}
			f[i][m - 1] = 1;
			for(int k = m - 2; k >= 0; --k) {
				if(a[i][k] < a[i][k + 1]) f[i][k] = 1 + f[i][k + 1];
				else f[i][k] = 1;
				res = max(res, f[i][k]);
			}
		}
		for(int i = 1; i < n; ++i) {
			for(int k = 0; k < m; ++k) {
				int low = k, high = k + f[i][k];
				while(low < high) {
					int mid = (low + high) >> 1;
					if(b[i - 1][mid] < mid - k + 1 || a[i - 1][mid] >= a[i][k]) high = mid;
					else low = mid + 1;
				}
				nxt[i][k] = high - k;
			}
		}
		int K = 31 - __builtin_clz(n);
		for(int c = 0; c < m; ++c) {
			for(int r = 0; r < n; ++r) 
				st[0][r] = nxt[r][c];
			for(int i = 1; i <= K; ++i)
				for(int k = 0; k + (1 << i) - 1 < n; ++k)
					st[i][k] = min(st[i - 1][k], st[i - 1][k + (1 << i - 1)]);
			for(int r = 0; r < n; ++r) {
				if(nxt[r][c]) {
					int L = 0, R = r;
					for(int k = K; k >= 0; --k) {
						int z = 1 << k;
						if(R + z < n && query(r, R + z) >= nxt[r][c]) R += z;
						if(L + z < r && query(L + z, r) < nxt[r][c]) L += z; 
					}
					res = max(res, nxt[r][c] * (R - L + 1));
				}
			}
		}
		cout << res << '\n';
	}
	return 0;
}