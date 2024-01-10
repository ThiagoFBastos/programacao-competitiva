#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n;

	cin >> n;

	vector<double> dp(n + 1);

	dp[n] = 21;

	for(int i = n - 1; i; --i) {
		dp[i] = 0;
		for(int x = 1; x <= 6; ++x)
			dp[i] += max((double)x, dp[i + 1] / 6);
	}

	cout << fixed << setprecision(12) << dp[1] / 6 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
