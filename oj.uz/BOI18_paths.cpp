#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 3e5 + 10;
const int M = 32;
 
int c[N], n, m, k;
i64 dp[2][N][M], ans;
 
vector<int> g[N];
 
void solve() {
	cin >> n >> m >> k;
 
	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		--c[i];
		dp[0][i][1 << c[i]] = 1;
	}
 
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for(int i = 1; i < k; ++i) {
 
		for(int u = 0; u < n; ++u)
		for(int j = 0; j < (1 << k); ++j)
			dp[1][u][j] = 0;
 
		for(int u = 0; u < n; ++u) {		
			for(int v : g[u]) {
				if(c[u] == c[v]) continue;
				for(int j = 0; j < (1 << k); ++j) {
					int a = 1 << c[u], b = 1 << c[v];
					if((a & ~j) || (b & j)) continue;
					dp[1][v][(1 << c[v]) | j] += dp[0][u][j];
				}
			}
		}
 
		for(int u = 0; u < n; ++u) {
			for(int j = 0; j < (1 << k); ++j) {
				dp[0][u][j] = dp[1][u][j];
				ans += dp[1][u][j];
			}
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
