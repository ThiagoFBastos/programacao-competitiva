#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

int dp[N][2];

void solve() {

	int n, c;

	cin >> n >> c;

	vector<int> t(n), a(n), ans(n, 0);

	for(int i = 0; i < n; ++i) cin >> t[i] >> a[i];

	for(int i = 0; i < 30; ++i) {

		for(int k = 0; k < 2; ++k) {
			dp[i][k] = k;
			for(int j = 1; j <= n; ++j) {
				int bit = !!(a[j - 1] & (1 << i));
				if(t[j - 1] == 1) dp[j][k] = dp[j - 1][k] & bit;			
				else if(t[j - 1] == 2) dp[j][k] = dp[j - 1][k] | bit;
				else dp[j][k] = dp[j - 1][k] ^ bit;
			}
		}
	
		int bit = !!(c & (1 << i));

		for(int j = 1; j <= n; ++j) {
			bit = dp[j][bit];
			ans[j - 1] ^= bit << i;
		}
	}

	for(int v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

