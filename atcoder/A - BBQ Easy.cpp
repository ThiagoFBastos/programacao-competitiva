#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
using i128 = __int128;

const int N = 1e2 + 10;
int dp[2 * N][N];

void solve() {
	int n;
	cin >> n;
	vector<int> l(2*n);
	for(int& v : l) cin >> v;
	sort(all(l));
	for(int i = 0; i <= 2 * n; ++i)
		for(int j = 0; j <= n; ++j)
			dp[i][j] = -INF;
	dp[0][0] = 0;
	for(int i = 1; i <= 2 * n; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(j) dp[i][j - 1] = max(dp[i][j - 1], dp[i - 1][j]);
			dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j]+ l[i - 1]);
		}
	}
	cout << dp[2*n][0] << '\n';
}
	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
