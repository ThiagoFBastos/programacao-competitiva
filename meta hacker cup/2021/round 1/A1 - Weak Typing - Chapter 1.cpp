#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int N = 8e5 + 1, inf = 1e9;

int dp[N][2];

void solve() {
	int n;
	string s;
	
	cin >> n >> s;
	
	dp[0][0] = dp[0][1] = 0;
	
	for(int i = 1; i <= n; ++i) {
		char ch = s[i - 1];
		if(ch == 'F') {
			dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + 1);
			dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + 1);
		} else if(ch == 'O') {
			dp[i][0] = inf;
			dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + 1);
		} else {
			dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + 1);
			dp[i][1] = inf;
		}
	}
	
	cout << min(dp[n][0], dp[n][1]) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
