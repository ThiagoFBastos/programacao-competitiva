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
using i128 = __int128;

const int N = 1e3 + 10;

int dp[2][N][N], lcp[N][N], k;
string s, t;

void solve() {
	while(true) {
		cin >> k;

		if(!k) break;

		cin >> s >> t;
		
		int n = s.size(), m = t.size();

		for(int i = 0; i <= n; ++i) {
			for(int j = 0; j <= m; ++j) {
				lcp[i][j] = dp[0][i][j] = 0;
				dp[1][i][j] = -INF;
			}
		}

		for(int i = n - 1; i >= 0; --i)
			for(int j = m - 1; j >= 0; --j)
				lcp[i][j] = s[i] == t[j] ? 1 + lcp[i + 1][j + 1] : 0;

		for(int i = 0; i <= n; ++i) {
			for(int j = 0; j <= m; ++j) {
				dp[0][i][j] = max(dp[0][i][j], dp[1][i][j]);
				if(s[i] == t[j]) {
					int l = lcp[i][j];
					if(l >= k) dp[1][i + k][j + k] = max(dp[1][i + k][j + k], dp[0][i][j] + k);
					dp[1][i+1][j+1] = max(dp[1][i+1][j+1], dp[1][i][j] + 1);
				}
				dp[0][i + 1][j] = max(dp[0][i + 1][j], dp[0][i][j]);
				dp[0][i][j + 1] = max(dp[0][i][j + 1], dp[0][i][j]);
			}
		}

		cout << dp[0][n][m] << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
