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
 
const int N = 401, INF = 1e9;
 
int dp[N][N][N][3];
 
void solve() {
	
	int n, r, g, y;
	string s, p = "RGY";
	vector<int> pos[3], cnt[3][3];
 
	cin >> n >> s;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < 3; ++j) {
			if(s[i] == p[j])
				pos[j].push_back(i);
		}
	}
 
	r = pos[0].size();
	g = pos[1].size();
	y = pos[2].size();
 
	for(int i = 0; i <= r; ++i)
	for(int j = 0; j <= g; ++j)
	for(int k = 0; k <= y; ++k)
	for(int l = 0; l < 3; ++l)
		dp[i][j][k][l] = INF;
 
	for(int i = 0; i < 3; ++i) {
		int n = pos[i].size();
		for(int j = 0; j < 3; ++j) {
			cnt[i][j].resize(n);
			for(int k = 0; k < n; ++k)
				cnt[i][j][k] = lower_bound(pos[j].begin(), pos[j].end(), pos[i][k]) - pos[j].begin();
		}
	}
 
	for(int l = 0; l < 3; ++l) dp[0][0][0][l] = 0;
 
	for(int i = 0; i <= r; ++i) {
 
		for(int j = 0; j <= g; ++j) {
 
			for(int k = 0; k <= y; ++k) {
 
				if(i > 0) {
					int moves = max(0, cnt[0][1][i - 1] - j) + max(0, cnt[0][2][i - 1] - k);
					dp[i][j][k][0] = min(dp[i][j][k][0], min(dp[i - 1][j][k][1], dp[i - 1][j][k][2]) + moves);
				}
 
				if(j > 0) {
					int moves = max(0, cnt[1][0][j - 1] - i) + max(0, cnt[1][2][j - 1] - k);
					dp[i][j][k][1] = min(dp[i][j][k][1], min(dp[i][j - 1][k][0], dp[i][j - 1][k][2]) + moves);
				}
 
				if(k > 0) {
					int moves = max(0, cnt[2][0][k - 1] - i) + max(0, cnt[2][1][k - 1] - j);
					dp[i][j][k][2] = min(dp[i][j][k][2], min(dp[i][j][k - 1][0], dp[i][j][k - 1][1]) + moves);
				}
			}
		}
	}
 
	int ans = min({dp[r][g][y][0], dp[r][g][y][1], dp[r][g][y][2]});
	if(ans == INF) ans = -1;
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
