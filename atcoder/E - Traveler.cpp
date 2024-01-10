#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const i64 linf = 1e16L;

void solve() {
	
	int n;

	cin >> n;

	vector<ii> a(n);
	vector<int> p;
	vector<vector<int>> X(n + 1);
	vector<vector<i64>> dp(n + 1);

	for(auto& [x, y] : a) {
		cin >> x >> y;
		p.push_back(y);
	}

	p.push_back(n + 1);
	sort(p.begin(), p.end());
	p.resize(unique(p.begin(), p.end()) - p.begin());

	for(auto [x, y] : a) {
		int k = lower_bound(p.begin(), p.end(), y) - p.begin();
		X[k].push_back(x);
	}

	X[(int)p.size() - 1].push_back(0);

	for(int i = 0; i < (int)p.size(); ++i) {
		dp[i].assign(X[i].size(), linf);
		sort(X[i].begin(), X[i].end());
	}

	for(int i = 0; i < (int)X[0].size(); ++i) dp[0][i] = abs(X[0][i]);

	for(int i = 0; i < (int)p.size() - 1; ++i) {

		i64 v1 = linf, v2 = linf;

		for(int j = 0; j < (int)X[i].size(); ++j) {
			v1 = min(v1, 2ll * (X[i][j] - X[i][0]) - X[i][j] + dp[i][j]);
			v2 = min(v2, 2ll * (X[i].back() - X[i][j]) + X[i][j] + dp[i][j]);
		}

		for(int j = 0; j < (int)X[i + 1].size(); ++j) {
			if(X[i + 1][j] >= X[i].back()) dp[i + 1][j] = min(dp[i + 1][j], v1 + X[i + 1][j]);
			if(X[i + 1][j] <= X[i].front()) dp[i + 1][j] = min(dp[i + 1][j], v2 - X[i + 1][j]);
		}

		v1 = linf;

		for(int k = 0, j = 0; j < (int)X[i + 1].size(); ++j) {

			while(k < (int)X[i].size() && X[i][k] <= X[i + 1][j]) {
				v1 = min(v1, 2ll * (X[i].back() - X[i].front()) + X[i][k] + dp[i][k]);
				++k;
			}

			if(X[i + 1][j] >= X[i].front() && X[i + 1][j] <= X[i].back())
				dp[i + 1][j] = min(dp[i + 1][j], v1 - X[i + 1][j]);
		}

		v1 = linf;

		for(int k = (int)X[i].size() - 1, j = (int)X[i + 1].size() - 1; j >= 0; --j) {

			while(k >= 0 && X[i][k] >= X[i + 1][j]) {
				v1 = min(v1, 2ll * (X[i].back() - X[i].front()) - X[i][k] + dp[i][k]);
				--k;
			}

			if(X[i + 1][j] >= X[i].front() && X[i + 1][j] <= X[i].back())
				dp[i + 1][j] = min(dp[i + 1][j], v1 + X[i + 1][j]);
		}
	}

	cout << dp[(int)p.size() - 1][0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

