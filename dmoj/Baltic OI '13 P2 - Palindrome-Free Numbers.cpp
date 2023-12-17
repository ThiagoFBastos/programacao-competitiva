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

i64 dp[20][2][11][11];

i64 count(i64 X) {
	if(X < 0) return 0;

	string s = to_string(X);

	for(int i = 0; i < 20; ++i)
	for(int j = 0; j < 2; ++j)
	for(int k = 0; k < 11; ++k)
	for(int l = 0; l < 11; ++l)
		dp[i][j][k][l] = 0;

	dp[0][1][10][10] = 1;

	int n = s.size();

	for(int i = 1; i <= n; ++i) {
		int c = s[i - 1] - '0';
		for(int d1 = 0; d1 <= 10; ++d1) {
			for(int d2 = 0; d2 <= 10; ++d2) {
				for(int d3 = 0; d3 <= 9; ++d3) {
					if(d2 == d3 || d1 == d3 || (!d3 && d2 == 10)) continue;
					if(d3 <= c) dp[i][d3 == c][d2][d3] += dp[i - 1][1][d1][d2];
					dp[i][0][d2][d3] += dp[i - 1][0][d1][d2];
				}
			}
		}
		dp[i][0][10][10] += dp[i - 1][0][10][10] + dp[i - 1][1][10][10];
	}

	i64 ans = 0;

	for(int i : {0, 1})
		for(int d1 = 0; d1 <= 10; ++d1)
			for(int d2 = 0; d2 <= 10; ++d2)
				ans += dp[n][i][d1][d2];

	return ans;
}

void solve() {
	i64 a, b;
	cin >> a >> b;
	cout << count(b) - count(a - 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
