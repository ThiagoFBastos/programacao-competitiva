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
int dist(char f, char t) {
	return min(abs(f - t), 26 - abs(f - t));
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int maxn = 401;
	int n, k, dp1[maxn][maxn], dp2[maxn][maxn];
	string s;
	cin >> n >> k >> s;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			dp1[i][j] = 0;
			dp2[i][j] = 10000;
		}
	}
	dp2[n][0] = 0;
	for(int a = 0; a < n - 1; ++a)
		if(s[a] != s[a + 1])
			dp1[a][a + 1] = dist(s[a], s[a + 1]);
	for(int a = 3; a <= n; ++a)
		for(int b = 0; b <= n - a; ++b)
			dp1[b][b + a - 1] = dp1[b + 1][b + a - 2] + dist(s[b + a - 1], s[b]);
	for(int b = n - 1; b >= 0; --b)
		for(int c = 1; c <= k; ++c)
			for(int a = b + 1; a <= n; ++a)
				dp2[b][c] = min(dp2[b][c], dp1[b][a - 1] + dp2[a][c - 1]);
	int ans = 10000;
	for(int i = 0; i <= k; ++i) ans = min(ans, dp2[0][i]);
	cout << ans << '\n';
	return 0;
}