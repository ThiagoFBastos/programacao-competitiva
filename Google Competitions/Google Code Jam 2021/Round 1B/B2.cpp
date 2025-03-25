#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1000;
long long dp[MAXN][21];
void solve() {
	int n, a, b, t = 0;
	cin >> n >> a >> b;
	vector<int> cnt(n + 1, 0);
	for(int i = 1; i <= n; ++i) cin >> cnt[i];
	for(int i = 0; i < MAXN; ++i) 
		for(int j = 0; j <= n; ++j)
			dp[i][j] = 0;
	vector<long long> tot(n + 1);
	for(int k = 1; k < MAXN ; ++k) {
		bool ok = true;
		if(k - a > 0) {
			for(int i = 1; i <= n; ++i)
				dp[k][i] += dp[k - a][i];
		}
		if(k - b > 0) {
			for(int i = 1; i <= n; ++i)
				dp[k][i] += dp[k - b][i];
		}
		for(int i = 1; i <= n; ++i) tot[i] = dp[k][i];
		for(int i = n; i > 0; --i) {
			if(!cnt[i]) continue;
			for(int j = 1; j < i; ++j) tot[j] -= cnt[i] * dp[i][j];
		}
		for(int i = 1; i <= n; ++i) {
			if(tot[i] < cnt[i]) {
				ok = false;
				break;
			}
		}
		if(ok) {
			cout << k << '\n';
			return;
		}
		if(k <= n) ++dp[k][k];
	}
	cout << "IMPOSSIBLE\n";
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}