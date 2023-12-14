#include "boxes.h"
 
#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
long long delivery(int N, int K, int L, int p[]) {
 
	vector<int> x[2];
	vector<i64> dp[2], mods(K, INFLL), pre(K + 1, INFLL);	
	i64 ans = INFLL, best = INFLL;
 
	for(int i = 0; i < N; ++i) {
		if(p[i] <= L / 2) x[1].pb(p[i]);
		else x[0].pb(L - p[i]);
	}
 
	reverse(all(x[0]));
 
	for(int i = 0; i < 2; ++i) {
		dp[i].resize(x[i].size() + 1);
		dp[i][0] = 0;
 
		for(int j = 1; j <= (int)x[i].size(); ++j)
			dp[i][j] = 2 * x[i][j - 1] + (j - K < 0 ? 0 : dp[i][j - K]);
	}
	
	for(int j = 0; j <= (int)x[1].size(); ++j) {
		int m = (int)x[1].size() - j;
		mods[m % K] = min(mods[m % K], (m + K - 1ll) / K * L + dp[1][j]);
		best = min(best, mods[m % K]);
	}
 
	pre[0] = INFLL;
	for(int i = 1; i < K; ++i) pre[i] = min(pre[i - 1], mods[i]);
	pre[K] = INFLL;
	
	for(int j = 0; j <= (int)x[0].size(); ++j) {
		int m = (int)x[0].size() - j;
		i64 c = (m + K - 1ll) / K * L + dp[0][j];
		ans = min(ans, c + min(best, pre[K - m % K] - L));
	}	
 
    return ans;
}
