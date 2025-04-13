#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 22;
long long dp[MAXN][10];
unsigned long long solve(long long n) {
	long long cnt = 0, p = 0;
	unsigned long long res = 0;
	int d, lastd = -1;
	for(d = 1; d < MAXN; ++d) {
		p = cnt;
		for(int k = 1; k < 10; ++k)
			cnt += dp[d][k];
		if(cnt >= n)
			break;
	}
	cnt = p;
	for(int k = 1; k <= 9; ++k) {
		p = cnt;
		cnt += dp[d][k];
		if(cnt >= n) {
			res = k;
			lastd = k;
			cnt = p;
			break;
		}
	}
	while(--d) {
		res *= 10;
		for(int k = 0; k <= 9; ++k) {
			if(lastd == 1 && k == 3) continue;
			p = cnt;
			cnt += dp[d][k];
			if(cnt >= n) {
				lastd = k;
				res += k;
				cnt = p;
				break;
			}
		}
	}
	return res;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int d = 1; d < MAXN; ++d)
		for(int k = 0; k < 10; ++k)
			dp[d][k] = 0;
	for(int k = 0; k < 10; ++k)
		dp[1][k] = 1;
	dp[1][4] = 0;
	for(int d = 2; d < MAXN; ++d) {
		long long cnt = 0;
		for(int k = 0; k < 10; ++k) 
			cnt += dp[d - 1][k];
		for(int k = 0; k < 10; ++k) {
			if(k == 4) continue;
			dp[d][k] += cnt;
			if(k == 1)
				dp[d][k] -= dp[d - 1][3];
		}
	}
	long long n;
	while(cin >> n) cout << solve(n) << '\n';
	return 0;
}