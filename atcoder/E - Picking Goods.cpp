#include "bits/stdc++.h"

using namespace std;

using ll = long long;
using ii = pair<int, int>;

const int N = 3e3;

int g[N][N];
ll dp[N][N][4];

void solve() {
	int r, c, k;

	cin >> r >> c >> k;

	while(k--) {
		int x, y;
		cin >> x >> y;
		cin >> g[x - 1][y - 1];
	}

	dp[0][0][1] = g[0][0];

	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {

			if(j > 0) {
				for(int k = 1; k <= 3; ++k)
					dp[i][j][k] = max(max(dp[i][j - 1][k], dp[i][j][k]), dp[i][j - 1][k - 1] + g[i][j]);
				dp[i][j][0] = dp[i][j - 1][0];
			}

			if(i > 0) {
				for(int k = 0; k <= 3; ++k) {
					dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][k]);
					dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][k] + g[i][j]);
				}
			}
		}
	}

	cout << *max_element(dp[r - 1][c - 1], dp[r - 1][c - 1] + 4) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

