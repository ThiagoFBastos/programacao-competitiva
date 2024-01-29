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

const int N = 1e3 + 100;

int dp[N][N], n, m;
vector<string> g;

void dfs(int i, int j) {
	dp[i][j] = 1;
	for(int dx = -1; dx <= 1; ++dx) {
		for(int dy = -1; dy <= 1; ++dy) {
			int _i = i + dx;
			int _j = j + dy;
			if(_i < 0 || _j < 0 || _i == n || _j == m || g[_i][_j] != 1 + g[i][j]) continue;
			if(dp[_i][_j] == -1) dfs(_i, _j);
			dp[i][j] = max(dp[i][j], 1 + dp[_i][_j]); 
		}
	}
}

void solve() {
	int ans = 0;
	cin >> n >> m;
	g.resize(n);	
	for(int i = 0; i < n; ++i) {
		cin >> g[i];
		for(int j = 0; j < m; ++j) dp[i][j] = -1;
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(dp[i][j] == -1) dfs(i, j);
			ans = max(ans, dp[i][j]);
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

