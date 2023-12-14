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
 
const int N = 1e3 + 10;
 
int a[N][N], tmp[N][N], n, m;
i64 ps[N][N];
 
void rotate() {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			tmp[j][n - i - 1] = a[i][j];
 
	swap(n, m);
 
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			a[i][j] = tmp[i][j];
}
 
void solve() {
	i64 ans = -INFLL;
 
	cin >> n >> m;
 
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> a[i][j];
 
	for(int i = 0; i <= max(n, m); ++i) ps[0][i] = ps[i][0] = INFLL;
 
	for(int k = 0; k < 4; ++k) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j) {
				ps[i][j] = a[i - 1][j - 1] - i - j;
				ps[i][j] = min(ps[i][j], ps[i - 1][j]);
				ps[i][j] = min(ps[i][j], ps[i][j - 1]);
				ans = max(ans, -i - j + a[i - 1][j -1] - ps[i][j] - 1);
			}
		}
		rotate();
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
