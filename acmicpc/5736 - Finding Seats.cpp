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
using i128 = __int128;

const int N = 3e2 + 10;

char grid[N][N];
int ps[N][N];

void solve() {
	while(true) {
		int n, m, k, ans = INF;

		cin >> n >> m >> k;

		if(n + m + k == 0) break;

		for(int i = 0; i < n; ++i) {
			cin >> grid[i];
			for(int j = 1; j <= m; ++j)
				ps[i][j] = ps[i][j - 1] + (grid[i][j - 1] == '.');
		}

		for(int l = 0; l < m; ++l) {
			for(int r = l; r < m; ++r) {
				int lo = 0, seats = 0;
				for(int i = 0; i < n; ++i) {
					seats += ps[i][r + 1] - ps[i][l];
					while(seats - ps[lo][r + 1] + ps[lo][l] >= k) {
						seats -= ps[lo][r + 1] - ps[lo][l];
						++lo;
					}
					if(seats >= k) ans = min(ans, (r - l + 1) * (i - lo + 1));
				}
			}
		}

		cout << ans << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
