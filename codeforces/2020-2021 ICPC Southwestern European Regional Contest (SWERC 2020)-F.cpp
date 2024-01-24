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

const int N = 2021 + 10;

int dp[N][N];

void solve() {
	int n, r, m;

	cin >> r >> n >> m;

	dp[0][0] = 1;

	for(int i = 1; i <= n; ++i) {
		if(i != r) {
			for(int j = 1; j < i; ++j) {
				if(j >= 2) {
					int c = j * (j - 1) / 2;
					dp[i][j - 2] = (dp[i][j - 2] + (i64)dp[i - 1][j] * c) % m;
				}
				dp[i][j - 1] = (dp[i][j - 1] + (i64)j * dp[i - 1][j]) % m;
			}
		}
		for(int j = n; j >= 0; --j) dp[i][j + 1] = (dp[i][j] + dp[i - 1][j]) % m; 
		dp[i][0] = 0;
	}

	cout << dp[n][1] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
