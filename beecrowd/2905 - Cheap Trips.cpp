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
#define f first
#define s second
const int maxn = 2e5 + 1;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	double dp[maxn];
	cin >> n;
	vii t(n);
	for(int i = 0; i < n; ++i)
		cin >> t[i].f >> t[i].s;
	dp[n] = 0;
	for(int i = n - 1; i >= 0; --i) {
		double cost = t[i].s;
		int tt = t[i].f;
		dp[i] = t[i].s + dp[i + 1];
		for(int k = i + 1; k < n && k - i < 6; ++k) {
			if(tt >= 120) break;
			else if(k == i + 1) cost += .5 * t[k].s;
			else cost += .25 * t[k].s;
			dp[i] = min(dp[i], cost + dp[k + 1]);
			tt += t[k].f;
		}
	}
	cout.precision(2);
	cout.setf(ios_base :: fixed);	
	cout << dp[0] << '\n';
	return 0;
}