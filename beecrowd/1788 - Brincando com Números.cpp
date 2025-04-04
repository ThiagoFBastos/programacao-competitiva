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
const int maxn = 1002, maxp = 1e7;
int dp[maxn][maxn][7], a[maxn][maxn], r, c, k;
char p;
bitset<maxp + 1> primo;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	primo.set();
	primo[0] = primo[1] = 0;
	for(int k = 4; k <= maxp; k += 2)
		primo[k] = 0;
	for(int k = 3; k * k <= maxp; k += 2) {
		if(primo[k]) {
			for(int i = k + k; i <= maxp; i += k) 
				primo[i] = 0;
		}
	}
	while(true) {
		cin >> r >> c >> k;
		if(!(r || c || k)) break;
		cin >> p;
		++r, ++c;
		for(int i = 0; i <= r; ++i) {
			for(int j = 0; j <= c; ++j) {
				a[i][j] = INT_MAX;
				for(int l = 0; l <= k; ++l)
					dp[i][j][l] = INT_MIN;
			}
		}
		--r, --c;
		for(int i = 1; i <= r; ++i) 
			for(int j = 1; j <= c; ++j) 
				cin >> a[i][j];
		if(p == 'N') {
			for(int i = 1; i <= r; ++i) {
				for(int j = c; j; --j) {
					int y = a[i][j];
					if(primo[y]) {
						for(int l = k; l >= 0; --l) {
							int x = 0;
							if(a[i - 1][j] < y) x = max(dp[i - 1][j][l], x);
							if(a[i][j + 1] < y) x = max(dp[i][j + 1][l], x);
							dp[i][j][l + 1] = max(dp[i][j][l + 1], 1 + max({dp[i - 1][j][l], dp[i][j + 1][l], 0}));
							dp[i][j][l] = 1 + x;
						}
					} else {
						for(int l = k; l >= 0; --l) {
							int x = 0;
							if(a[i - 1][j] < y) x = max(dp[i - 1][j][l], x);
							if(a[i][j + 1] < y) x = max(dp[i][j + 1][l], x);
							dp[i][j][l] = 1 + x;
						}
					}
				}
			}
		} else {
			for(int i = r; i; --i) {
				for(int j = 1; j <= c; ++j) {
					int y = a[i][j];
					if(primo[y]) {
						for(int l = k; l >= 0; --l) {
							int x = 0;
							if(a[i + 1][j] < y) x = max(dp[i + 1][j][l], x);
							if(a[i][j - 1] < y) x = max(dp[i][j - 1][l], x);
							dp[i][j][l + 1] = max(dp[i][j][l + 1], 1 + max({dp[i + 1][j][l], dp[i][j - 1][l], 0}));
							dp[i][j][l] = 1 + x;
						}
					} else {
						for(int l = k; l >= 0; --l) {
							int x = 0;
							if(a[i + 1][j] < y) x = max(dp[i + 1][j][l], x);
							if(a[i][j - 1] < y) x = max(dp[i][j - 1][l], x);
							dp[i][j][l] = 1 + x;
						}
					}
				}
			}
		}
		int res {};
		for(int i = 1; i <= r; ++i)
			for(int j = 1; j <= c; ++j)
				for(int l = 0; l <= k; ++l)
					res = max(res, dp[i][j][l]);
		cout << res << '\n';
	}
	return 0;
}