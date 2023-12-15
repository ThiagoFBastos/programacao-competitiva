#include "bits/stdc++.h"
 
using namespace std;
 
const long long inf = 1e17L;
 
int n, k;
vector<vector<long long>> dp;
vector<int> pre;
 
void dc(int k, int lo, int hi, int l, int r) {
	if(l > r) return;
	
	int mid = (l + r) / 2;
	auto p = make_pair(inf, 0);
	
	for(int i = lo; i <= min(hi, mid - 1); ++i) p = min(p, make_pair(dp[k - 1][i] + (pre[mid] - pre[i] + 0LL) * (pre[mid] - pre[i]), i));
	
	dp[k][mid] = p.first;
	
	dc(k, lo, p.second, l, mid - 1);
	dc(k, p.second, hi, mid + 1, r);
}
 
void solve() {
	cin >> n >> k;
	
	pre.resize(n + 1);	
	pre[0] = 0;
	
	dp = vector<vector<long long>>(k + 1, vector<long long>(n + 1, inf));
	dp[0][0] = 0;
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
	}
	
	for(int i = 1; i <= k; ++i) dc(i, 0, n, 0, n);
	
	cout << dp[k][n] << '\n';
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
