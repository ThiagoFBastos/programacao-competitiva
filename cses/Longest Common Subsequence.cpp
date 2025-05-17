#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e3 + 5, INF = 1e9;
 
int dp[N][N];
 
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
 
	cin >> n >> m;
 
	vector<int> a(n), b(m), c;
 
	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;
 
	for(int i = 0; i <= n + 1; ++i)
		for(int j = 0; j <= m + 1; ++j)
			dp[i][j] = -INF;
 
	dp[n][m] = 0;
 
	for(int i = n; i >= 0; --i) {
		for(int j = m ; j >= 0; --j) {
			if(i < n && j < m && a[i] == b[j]) dp[i][j] = 1 + dp[i + 1][j + 1];
			dp[i][j] = max({dp[i][j], dp[i + 1][j], dp[i][j + 1]});
		}
	}
 
	int target = dp[0][0], i = 0, j = 0;
 
	while(i < n && j < m) {
		if(a[i] == b[j] && dp[i][j] == target) {
			c.push_back(a[i]);
			++i, ++j, --target;
		} else if(dp[i + 1][j] == target) ++i;
		else if(dp[i][j + 1] == target) ++j;
	}
 
	cout << c.size() << '\n';
	for(int v : c) cout << v << ' ';
	cout << '\n';
 
	return 0;
}
