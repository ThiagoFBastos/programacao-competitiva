#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 3e5 + 100;
const i64 INF = 1e17L;

i64 dp[N][2];

i64 DP(vector<int>& w) {
	int n = w.size();

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < 2; ++j)
		dp[i][j] = INF;

	dp[0][1] = w[0];

	for(int i = 1; i < n; ++i) {
		dp[i][0] = dp[i - 1][1];
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + w[i];
	}

	return min(dp[n - 1][1], dp[n - 2][1]);
}

void solve() {

	int n;

	cin >> n;

	vector<int> w(n);
	for(int& v : w) cin >> v;

	i64 ans = DP(w);
	w.push_back(w[0]);
	w.erase(w.begin());
	cout << min(ans, DP(w)) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
