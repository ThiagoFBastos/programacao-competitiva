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
int dp[50][100001];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MOD = 1e9 + 7;
	int t, n, m;
	cin >> t >> m >> n;
	for(int i = 0; i < t; ++i)
		for(int k = m; k <= n; ++k)
			dp[i][k] = 0;
	for(int i = m; i <= n; ++i) dp[0][i] = 1;
	for(int i = 0; i < t - 1; ++i) {
		for(int k = m; k <= n; ++k) {
			dp[i + 1][k + 1] += dp[i][k];
			dp[i + 1][k - 1] += dp[i][k];
			if(dp[i + 1][k + 1] >= MOD) dp[i + 1][k + 1] -= MOD;
			if(dp[i + 1][k - 1] >= MOD) dp[i + 1][k - 1] -= MOD;
		}
	}
	int ans = 0;
	for(int i = m; i <= n; ++i) {
		ans += dp[t - 1][i];
		if(ans >= MOD) ans -= MOD;
	} 
	cout << ans << '\n';
 	return 0;
}