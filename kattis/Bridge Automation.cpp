#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
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

const int inf = 1e9;
int n, dp[4000][1801], p[1802];
vi t;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	t.resize(n);
	for(int i = 0; i < n; ++i) cin >> t[i];
	for(int k = 0; k <= 1800; ++k) dp[0][k] = 60;
	for(int k = 1; k < n; ++k) {
		int ans = inf;
		fill(p, p + 1801, inf);
		fill(dp[k], dp[k] + 1801, inf);
		for(int i = 0; i <= 1800; ++i) {
			int a = t[k - 1] + i;			
			if(a + 20 <= t[k]) ans = min(ans, t[k] - a - 20 + dp[k - 1][i]);
			else dp[k][a + 20 - t[k]] = min(dp[k][a + 20 - t[k]], dp[k - 1][i]);
			p[max(a + 140, t[k]) - t[k]] = min(p[max(a + 140, t[k]) - t[k]], dp[k - 1][i] + 120);
		}
		for(int i = 0; i <= 1800; ++i) {
			dp[k][i] = min(dp[k][i], min(ans + i, p[i]));
			p[i + 1] = min(p[i + 1], p[i]);
		}
	}
	cout << 20 * n + *min_element(dp[n - 1], dp[n - 1] + 1801) + 60 << '\n';
	return 0;
}