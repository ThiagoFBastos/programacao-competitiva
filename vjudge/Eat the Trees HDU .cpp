#include <iostream>
#include <utility>

using namespace std;
/*
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
*/

int a[11][11];
int n, m, tcase;

long long	dp[2][1 << 11][2];

void solve() {
	cin >> n >> m;

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
		cin >> a[i][j];

	for(int i = 0; i < (1 << m); ++i)
	for(int j = 0; j < 2; ++j)
		dp[0][i][j] = 0;
	
	dp[0][0][0] = 1;

	for(int i = 0; i < n; ++i) {

		int bad = 0;

		for(int j = 0; j < m; ++j) bad |= (1 - a[i][j]) << j;

		for(int k = 0; k < (1 << m); ++k) if(k & bad) dp[0][k][0] = 0;

		for(int j = 1; j < m; ++j) {
			for(int k = 0; k < (1 << m); ++k) dp[1][k][0] = dp[1][k][1] = 0;

			for(int k = 0; k < (1 << m); ++k) {
				dp[1][k][0] += dp[0][k][1];
				if((k & (1 << (j - 1))) || !a[i][j - 1]) dp[1][k][0] += dp[0][k][0];
				int mask = 3 << (j - 1);
				if(!(mask & bad)) dp[1][k ^ mask][(k >> j) & 1] += dp[0][k][0];
			}

			for(int k = 0; k < (1 << m); ++k) {
				dp[0][k][0] = dp[1][k][0];	
				dp[0][k][1] = dp[1][k][1];
			}
		}

		for(int k = 0; k < (1 << m); ++k) {
			if((~k & (1 << (m - 1))) && a[i][m-1]) dp[0][k][0] = 0;
			dp[0][k][0] += dp[0][k][1];
			dp[0][k][1] = 0;
		}
	}

	cout << "Case " << ++tcase << ": ";
	cout << "There are " << dp[0][0][0] << " ways to eat the trees.\n";
}

int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


