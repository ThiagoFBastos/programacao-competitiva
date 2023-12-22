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

const int N = 5e2 + 10;

int n, m, cnt, c[N][N], dp[N][N], pt[N * N], pt2[N][N];

void solve() {
	cin >> n >> m;

	for(int i = 0; i <= n; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			if(c[i][j] >= m) c[i][j] -= m;
		}
	}

	pt[0] = 1;
	for(int i = 1; i <= n * n; ++i) pt[i] = 2 * pt[i - 1] % m;

	for(int i = 1; i <= n; ++i) {
		pt2[i][0] = 1;
		for(int j = 1; j <= n; ++j)
			pt2[i][j] = (i64)pt2[i][j - 1] * (pt[i] - 1) % m;
	}

	dp[n - 1][1] = 1;

	for(int i = n - 1; i > 1; --i) {
		for(int k = 1; k < n; ++k) {
			for(int j = 1; j < i; ++j) {
				i64 ways = (i64)c[i - 1][j] * dp[i][k] % m * pt2[k][j] % m * pt[j * (j - 1) / 2];
				dp[i - j][j] = (dp[i - j][j] + ways) % m;
			}
		}
	}

	for(int i = 1; i < n; ++i) cnt = (cnt + dp[1][i] * (pt[i] - 1ll)) % m;

	cout << (cnt + m) % m << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
