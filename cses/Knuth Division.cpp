#include "bits/stdc++.h"
#define endl '\n'
 
using namespace std;
 
const long long inf = 1e16L;
 
void solve() {
	int n;
	
	cin >> n;
	
	vector<long long> pre(n + 1);
	vector<int> p(n + 2), _(n + 1);
	vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
	
	pre[0] = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		p[i] = i;
		pre[i] += pre[i - 1];
	}
	
	p[n + 1] = n;
		
	for(int k = 2; k <= n; ++k) {
		for(int R = k; R <= n; ++R) {
			int L = R - k + 1;
			auto ans = make_pair(inf, 0);
			for(int i = p[L]; i <= min(p[L + 1], R - 1); ++i) ans = min(ans, {dp[L][i] + dp[i + 1][R], i});
			dp[L][R] = ans.first + pre[R] - pre[L - 1];
			_[L] = ans.second;
		}
		for(int i = 1; i <= n; ++i) p[i] = _[i];
	}
	
	cout << dp[1][n] << endl;
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
