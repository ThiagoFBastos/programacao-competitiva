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
const int maxn = 304;
bool p[maxn], dp[maxn][maxn][maxn];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, c1, c2, c3, s = 0;
	bool ok = false;
	cin >> n >> c1 >> c2 >> c3;
	fill(p, p + maxn, true);
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		s += a;
		if(i < n - 1) p[s] = false;
	}
	dp[0][0][0] = true;
	for(int k = 0; k <= c1; ++k) {
		if(k > s) break;
		for(int i = 0; i <= c2; ++i) {
			if(k + 2 * i > s) break;
			for(int j = 0; j <= c3; ++j) {
				int x = k + 2 * i + 3 * j;
				if(x > s) break;
				else if(x == s) ok |= dp[k][i][j];
				dp[k + 1][i][j] |= p[x + 1] && dp[k][i][j];
				dp[k][i + 1][j] |= p[x + 2] && dp[k][i][j];
				dp[k][i][j + 1] |= p[x + 3] && dp[k][i][j];
			}
		}
	}
	cout << (ok ? "YES\n" : "NO\n");
	return 0;
}