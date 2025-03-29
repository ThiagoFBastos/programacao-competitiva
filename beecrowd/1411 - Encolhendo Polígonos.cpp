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
const int maxn = 1e4 + 1;
int a[maxn], dp[maxn], n;
int solve(int l, int k) {
	int lo = 0, R = 0, S = 0, max_points = 0;
	for(int i = 1; i <= n; ++i) {
		while(lo < i && R - S > l) {
			S += a[lo];
			++lo;
		}
		dp[i] = 0;
		if(R - S == l)
			dp[i] = 1 + dp[lo];
		R += a[i];
		max_points = max(max_points, dp[i]);
	}
	return max_points >= k - 1 ? k : -1;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(;;) {	
		int s = 0, ans = -1;
		cin >> n;	
		if(n == 0) break;
		for(int i = 1; i <= n; ++i) {
			cin >> a[i];
			s += a[i];
		}
		for(int i = 1; i * i <= s; ++i) {
			if(s % i) continue;
			else if(i > n) break;
			if(i >= 3) ans = max(ans, solve(s / i, i));
			if(s / i >= 3 && s / i <= n) ans = max(ans, solve(i, s / i));
		}
		cout << (ans < 0 ? -1 : n - ans) << '\n';
	}
	return 0;
}