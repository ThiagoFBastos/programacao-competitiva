#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e2 + 10;

char grid[N][N];
int n, m, xo, yo, q, dp[N][N];

void solve() {
	cin >> n >> m >> xo >> yo >> q;

	--xo, --yo;

	for(int i = 0; i < n; ++i) {
		cin >> grid[i];
		for(int j = 0; j < m; ++j)	
			dp[i][j] = -INF;
	}

	dp[xo][yo] = 0;

	while(q--) {
		int a, b, d;

		cin >> a >> b >> d;

		b = b - a + 1;

		if(d == 1) {
			for(int j = 0; j < m; ++j) {
				deque<ii> q;
				for(int i = n - 1; i >= 0; --i) {
					if(grid[i][j] == 'x') q.clear();
					while(!q.empty() && q.back().fi < dp[i][j] + i) q.pop_back();
					q.pb({dp[i][j] + i, i});
					while(q.front().sc > i + b) q.pop_front();
					dp[i][j] = grid[i][j] == '.' ? q.front().fi - i : -INF; 
				}
			}
		} else if(d == 2) {
			for(int j = 0; j < m; ++j) {
				deque<ii> q;
				for(int i = 0; i < n; ++i) {
					if(grid[i][j] == 'x') q.clear();
					while(!q.empty() && q.back().fi < dp[i][j] - i) q.pop_back();
					q.pb({dp[i][j] - i, i});
					while(q.front().sc < i - b) q.pop_front();
					dp[i][j] = grid[i][j] == '.' ? q.front().fi + i : -INF; 
				}
			}
		} else if(d == 3) {
			for(int i = 0; i < n; ++i) {
				deque<ii> q;
				for(int j = m - 1; j >= 0; --j) {
					if(grid[i][j] == 'x') q.clear();
					while(!q.empty() && q.back().fi < dp[i][j] + j) q.pop_back();
					q.pb({dp[i][j] + j, j});
					while(q.front().sc > j + b) q.pop_front();
					dp[i][j] = grid[i][j] == '.' ? q.front().fi - j : -INF;
				}
			}
		} else {
			for(int i = 0; i < n; ++i) {
				deque<ii> q;
				for(int j = 0; j < m; ++j) {
					if(grid[i][j] == 'x') q.clear();
					while(!q.empty() && q.back().fi < dp[i][j] - j) q.pop_back();
					q.pb({dp[i][j] - j, j});
					while(q.front().sc < j - b) q.pop_front();
					dp[i][j] = grid[i][j] == '.' ? q.front().fi + j : -INF;
				}
			}
		}
	}

	int ans = -INF;
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
		ans = max(ans, dp[i][j]);
	
	cout << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}
