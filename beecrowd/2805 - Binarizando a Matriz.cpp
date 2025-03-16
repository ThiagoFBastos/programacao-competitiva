#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7, maxn = 102;
int n, m, x[maxn][maxn], z[maxn][maxn], o[maxn][maxn], cnt = 0, dp[maxn][maxn];
char M[maxn][maxn];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i <= n + 1; ++i)
		for(int j = 0; j <= m + 1; ++j)
			dp[i][j] = z[i][j] = o[i][j] = x[i][j] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			cin >> M[i - 1][j - 1];
			if(M[i - 1][j - 1] == '1') {
				++o[1][1];
				--o[i + 1][1];
				--o[1][j + 1];
				++o[i + 1][j + 1];
			} else if(M[i - 1][j - 1] == '0') ++z[i][j];
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			o[i][j] += o[i - 1][j] + o[i][j - 1] - o[i - 1][j - 1];
			z[i][j] += z[i - 1][j] + z[i][j - 1] - z[i - 1][j - 1];
			if(o[i][j] && M[i - 1][j - 1] == '0' || z[i][j] && M[i - 1][j - 1] == '1') cnt = -1;
			else if(o[i][j]) x[i][j] = 1;
			else if(z[i][j]) x[i][j] = 0;
			else x[i][j] = -1;
		}
	}
	if(cnt == -1) cout << "0\n";
	else {
		for(int k = 1; k <= n; ++k) {
			if(x[k][1] == 0) break;
			else if(x[k + 1][1] != 1) dp[k][1] = 1;
		}
		if(x[1][1] != 1) ++cnt;
		for(int k = n; k; --k) {
			for(int i = 1; i <= m; ++i) {
				if(x[k][i] == 0) break;
				else if(x[k][i] == 1 && x[k + 1][i + 1] == 1) 
					continue;
				else if(x[k][i + 1]) {
					dp[k][i + 1] += dp[k][i];
					if(dp[k][i + 1] >= mod) 
						dp[k][i + 1] -= mod;
				}
				if(x[k - 1][i]) {
					dp[k - 1][i] += dp[k][i];
					if(dp[k - 1][i] >= mod)
						dp[k - 1][i] -= mod;
				}
			}
		}
		for(int i = m; i; --i) {
			cnt += dp[1][i];
			if(cnt >= mod) cnt -= mod;
			if(x[1][i] == 1) break;
		}
		cout << cnt << '\n';
	}
	return 0;
}