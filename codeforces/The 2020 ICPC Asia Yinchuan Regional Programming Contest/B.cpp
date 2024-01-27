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

const int N = 1e4 + 10;

int dp[N], parcial[N][4], a[N];

void solve() {
	int n;

	cin >> n;

	for(int i = 1; i <= n; ++i) cin >> a[i];

	dp[0] = 0;
	for(int i = 1; i <= n; ++i) dp[i] = -INF;

	for(int i = 1; i <= n; ++i) {

		for(int j = 0; j <= n; ++j)
			for(int k = 0; k <= 3; ++k)
				parcial[j][k] = -INF;

		for(int j = 1; j <= n; ++j) {
			parcial[j][0] = max(parcial[j - 1][0], dp[j - 1]);
			parcial[j][1] = max(parcial[j - 1][1], max(dp[j - 1], parcial[j - 1][0]) - a[j]);
			parcial[j][2] = max(parcial[j - 1][2], max(dp[j - 1], parcial[j - 1][0]) + a[j]);
			parcial[j][3] = max(parcial[j - 1][3], dp[j - 1]);
			parcial[j][3] = max(parcial[j][3], parcial[j - 1][0]); 
			parcial[j][3] = max(parcial[j][3], parcial[j - 1][2] - a[j]);
			parcial[j][3] = max(parcial[j][3], parcial[j - 1][1] + a[j]);
		}

		for(int j = 0; j <= n; ++j) dp[j] = parcial[j][3];

		cout << dp[n] << '\n';
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
 
