#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int n, m, k, p[100][100], dist[16][16], d[100][100], dp[1 << 15][15];
	char grid[100][101];
	while(true) {
		int s = 1;
		cin >> n >> m >> k;
		if(!(n || m || k)) break;
		for(int i = 0; i < n; ++i) cin >> grid[i];
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(grid[i][j] == 'C')
					p[i][j] = 0;
				else if(grid[i][j] == 'P') 
					p[i][j] = s++;
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(isupper(grid[i][j])) {
					queue<ii> Q;
					for(int a = 0; a < n; ++a)
						for(int b = 0; b < m; ++b) {
							if(grid[a][b] == '#') d[a][b] = 0;
							else d[a][b] = -1;
						}
					d[i][j] = 0;
					Q.push({i, j});
					while(!Q.empty()) {
						auto [x, y] = Q.front();
						Q.pop();
						if(isupper(grid[x][y]))
							dist[p[i][j]][p[x][y]] = dist[p[x][y]][p[i][j]] = d[x][y]; 
						if(x) {
							if(y >= 2 && d[x - 1][y - 2] == -1) {
								d[x - 1][y - 2] = 1 + d[x][y];
								Q.push({x - 1, y - 2});
							}
							if(y < m - 2 && d[x - 1][y + 2] == -1) {
								d[x - 1][y + 2] = 1 + d[x][y];
								Q.push({x - 1, y + 2});
							} 
						}
						if(x < n - 1) {
							if(y >= 2 && d[x + 1][y - 2] == -1) {
								d[x + 1][y - 2] = 1 + d[x][y];
								Q.push({x + 1, y - 2});
							}
							if(y < m - 2 && d[x + 1][y + 2] == -1) {
								d[x + 1][y + 2] = 1 + d[x][y];
								Q.push({x + 1, y + 2});
							} 
						}
						if(y) {
							if(x >= 2 && d[x - 2][y - 1] == -1) {
								d[x - 2][y - 1] = 1 + d[x][y];
								Q.push({x - 2, y - 1});
							}
							if(x < n - 2 && d[x + 2][y - 1] == -1) {
								d[x + 2][y - 1] = 1 + d[x][y];
								Q.push({x + 2, y - 1});
							} 
						}
						if(y < m - 1) {
							if(x >= 2 && d[x - 2][y + 1] == -1) {
								d[x - 2][y + 1] = 1 + d[x][y];
								Q.push({x - 2, y + 1});
							}
							if(x < n - 2 && d[x + 2][y + 1] == -1) {
								d[x + 2][y + 1] = 1 + d[x][y];
								Q.push({x + 2, y + 1});
							} 
						}
					}
				}
			}
		}
		int K = 1 << k;
		for(int i = 0; i < K; ++i)
			for(int j = 0; j < k; ++j)
				dp[i][j] = INT_MAX;
		for(int i = 0; i < k; ++i)
			dp[1 << i][i] = dist[0][i + 1];
		
		for(int i = 0; i < k; ++i) dp[0][i] = 0;
		for(int i = 1; i < K; ++i) {
			int a = 1, b;
			for(int j = 0; j < k; ++j) {
				if(i & a) {
					int r = i ^ a;
					b = 1;
					for(int h = 0; h < k; ++h) {
						if(r & b)
							dp[i][h] = min(dp[i ^ b][j] + dist[h + 1][j + 1], dp[i][h]);
						b <<= 1;
					}
				}
				a <<= 1;
			}
		}
		int ans = INT_MAX;
		for(int i = 0; i < k; ++i)
			ans = min(ans, dp[K - 1][i] + dist[0][i + 1]);
		cout << ans << '\n';
	}
	return 0;
}