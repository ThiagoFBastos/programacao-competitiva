#include "bits/stdc++.h"
#define endl '\n'
 
using namespace std;
 
const long long inf = 1e15L;
 
int n, k;
vector<long long> dp[2], f, g;
 
auto C(int l, int r) {
	if(!l) return r * g[r] - f[r];
	int mid = (l + r) / 2;
	return r * (g[r] - g[mid]) - (f[r] - f[mid]) + (f[mid] - f[l - 1]) - l * (g[mid] - g[l - 1]);
}
 
void divide_and_conquer(int lo, int hi, int l, int r) {
	if(l > r) return;
	
	int mid = (l + r) / 2;
	
	auto ans = make_pair(inf, 0);
	
	for(int i = lo; i <= min(hi, r - 1); ++i)
		ans = min(ans, {C(i, mid) + dp[0][i], i});
		
	dp[1][mid] = ans.first;
	
	divide_and_conquer(lo, ans.second, l, mid - 1);
	divide_and_conquer(ans.second, hi, mid + 1, r);
}
 
void solve() {
	cin >> n >> k;
	
	f.resize(n + 1);
	g.resize(n + 1);
	for(int i = 0; i < 2; ++i) dp[i].assign(n + 1, inf);
	
	dp[0][0] = f[0] = g[0] = 0;
	
	for(int i = 1; i <= n; ++i) {
		cin >> g[i];
		f[i] = f[i - 1] + i * g[i];
		g[i] += g[i - 1];
	}
	
	for(int i = 1; i <= k; ++i) {
		divide_and_conquer(0, n, 0, n);
		copy(dp[1].begin(), dp[1].end(), dp[0].begin());
	}
	
	auto ans = inf;
	
	for(int i = 1; i <= n; ++i) ans = min(ans, dp[0][i] + f[n] - f[i - 1] - i * (g[n] - g[i - 1]));
	
	cout << ans << endl;
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
