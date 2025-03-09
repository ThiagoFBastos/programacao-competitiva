#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
bool cover(ii a, ii b) {
	return max(a.second, b.second) <= min(a.first, b.first) && a.second < b.second && a.first < b.first; 
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MOD = 1e8;
	int n, m, dp[100][100];
	pair<int, int> t[100];
	while(true) {
		cin >> m >> n;
		if(!(n || m)) break;
		for(int i = 0; i < n; ++i)
			cin >> t[i].second >> t[i].first;
		sort(t, t + n);
		for(int i = 0; i < n; ++i)
			for(int k = 0; k < n; ++k)
				dp[i][k] = 0;
		for(int i = 0; i < n; ++i)
			if(t[i].second == 0)
				dp[i][i] = 1;
		for(int i = 0; i < n; ++i) {
			for(int k = 0; k < i; ++k) {
				if(cover(t[k], t[i])) {
					dp[i][k] += dp[k][k];
					if(dp[i][k] >= MOD) dp[i][k] -= MOD;
					for(int j = 0; j < k; ++j) {
						if(t[i].second > t[j].first) {
							dp[i][k] += dp[k][j];
							if(dp[i][k] >= MOD) dp[i][k] -= MOD;
						}
					}
				}
			}
		}
		int count = 0;
		for(int i = 0; i < n; ++i) {
			if(t[i].first == m) {
				for(int k = 0; k < n; ++k) {
					count += dp[i][k];
					if(count >= MOD) count -= MOD;
				}
			}
		}
		cout << count << '\n';
	}
	return 0;
}