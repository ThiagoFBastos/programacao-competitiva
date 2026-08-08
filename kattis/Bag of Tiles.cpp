#include "bits/stdc++.h"

using namespace std;

const int N = 1e4 + 1;
int a[30], cnt_sum[31][N], cnt[31];

auto subset_sum(int v[], int n) {
	vector<int> sum(1 << n);
	sum[0] = 0;
	for(int i = 1; i < (1 << n); ++i) sum[i] = sum[i - (i & -i)] + v[__builtin_ctz(i)];
	return sum;
}

void solve() {
	int m, n, t, win = 0, loose = 0;
	cin >> m;
	
	for(int i = 0; i < m; ++i) cin >> a[i];
	
	cin >> n >> t;
	
	if(m <= 15) {
		auto dp = subset_sum(a, m);
		for(int k = 0; k < (1 << m); ++k) {
			if(__builtin_popcount(k) != n) continue;
			else if(dp[k] == t) ++win;
			else ++loose;
		}
	} else {
		auto dp1 = subset_sum(a, m / 2);
		auto dp2 = subset_sum(a + m / 2, (m + 1) / 2);
		
		memset(cnt, 0, sizeof cnt);
		
		for(int k = 0; k < (1 << (m + 1) / 2); ++k) {
			int l = __builtin_popcount(k);
			++cnt[l];
			if(dp2[k] <= t) ++cnt_sum[l][dp2[k]];
		}
		
		for(int k = 0; k < (1 << (m / 2)); ++k) {
			int l = __builtin_popcount(k);
			if(l > n) continue;
			if(dp1[k] <= t) win += cnt_sum[n - l][t - dp1[k]];
			loose += cnt[n - l];
		}
		
		loose -= win;
		
		for(int k = 0; k < (1 << (m + 1) / 2); ++k) if(dp2[k] <= t) cnt_sum[__builtin_popcount(k)][dp2[k]] = 0;
	}
	
	cout << win << " : " << loose << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Game " << k << " -- ";
		solve();
	}
 	return 0;
}