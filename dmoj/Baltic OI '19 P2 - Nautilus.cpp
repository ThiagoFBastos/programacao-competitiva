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

const int N = 505;

bitset<N> dp[2][N], grid[N];

void solve() {
	int r, c, m;	
	string s;

	cin >> r >> c >> m;

	for(int i = 1; i <= r; ++i) {
		string l;
		cin >> l;
		for(int j = 0; j < c; ++j) grid[i][j] = l[j] == '.';
	}

	cin >> s;
	
	for(int i = 1; i <= r; ++i) dp[0][i] = grid[i];

	for(int i = 0; i < m; ++i) {

		for(int k = 1; k <= r; ++k) dp[1][k].reset();

		for(int k = 1; k <= r; ++k) {
			if(s[i] == '?' || s[i] == 'N') dp[1][k - 1] |= dp[0][k];
			if(s[i] == '?' || s[i] == 'S') dp[1][k + 1] |= dp[0][k];
			if(s[i] == '?' || s[i] == 'W') dp[1][k] |= dp[0][k] >> 1;
			if(s[i] == '?' || s[i] == 'E') dp[1][k] |= dp[0][k] << 1;
		}

		for(int k = 1; k <= r; ++k) {
			swap(dp[0][k], dp[1][k]);
			dp[0][k] &= grid[k];
		}
	}

	int cnt = 0;
	for(int k = 1; k <= r; ++k) cnt += dp[0][k].count();

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
