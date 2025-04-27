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
string restore(ll n, int m, int y) {
	ll dp[25][10], F[25];
	memset(F, 0, sizeof F);
	memset(&dp[0][0], 0, sizeof dp);
	for(int k = 0; k <= 9; ++k)
		dp[0][k] = 1;
	F[0] = 8;
	dp[0][m] = 0;
	for(int i = 1; i < 25; ++i) {
		ll cnt = 0;
		for(int k = 0; k < 10; ++k) 
			cnt += dp[i - 1][k];
		for(int k = 0; k <= 9; ++k) {
			if(k == m) continue;
			else if(k == y / 10)
				F[i] += dp[i][k] = cnt - dp[i - 1][y % 10];
			else
				F[i] += dp[i][k] = cnt;
		}
		F[i] -= dp[i][0];
	}
	ll cnt = 0;
	int i = 0;	
	string res;
	while(cnt < n) cnt += F[i++];
	--i;
	if(cnt >= n) cnt -= F[i];
	for(int d = 1; d <= 9; ++d) {
		if(cnt + dp[i][d] >= n) {
			res += d + '0';
			break;
		}
		cnt += dp[i][d];
	}
	while(--i >= 0) {
		for(int d = 0; d <= 9; ++d) {
			if(res.back() == y / 10 + 48 && d == y % 10) 
				continue;
			else if(cnt + dp[i][d] >= n) {
				res += d + '0';
				break;
			}
			cnt += dp[i][d];
		}
	}
	return res;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n;
	int m, y;
	while(cin >> n >> m >> y)
		cout << restore(n, m, y) << '\n';
 	return 0;
}