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

const int N = 3e3 + 100;

int dp[N][N], best[N], n, m, a[N];

void solve() {

	fill(best, best + N, INF);

	cin >> n >> m;

	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	for(int i = 0; i < N; ++i) dp[0][i] = INF;

	dp[0][0] = best[0] = 0;

	for(int i = 1; i <= n; ++i) {
		
		for(int j = 0; j <= m; ++j) 
			dp[i][j] = INF;

		for(int j = 0; a[i] + j <= m; ++j) {
			dp[i][j + a[i]] = min(dp[i - 1][j], dp[i][j + a[i]]);				
			dp[i][j + a[i]] = min(dp[i][j + a[i]], best[j] + 1);
		}

		for(int j = 0; j <= m; ++j) 
			best[j] = min(best[j], dp[i][j]);
	}
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) dp[i][j] += i < n;
		for(int j = 1; j <= m; ++j)
			dp[i][j] = min(dp[i][j], dp[i - 1][j]);
	}

	for(int i = 1; i <= m; ++i) cout << (dp[n][i] > n ? -1 : dp[n][i]) << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
    return 0;
}
