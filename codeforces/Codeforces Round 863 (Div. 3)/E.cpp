#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

i64 dp[20][2];

i64 count_numbers(i64 n) {
	string s = to_string(n);
	dp[0][0] = 0;
	dp[0][1] = 1;
	for(int i = 1; i <= (int)s.size(); ++i) {
		dp[i][0] = dp[i][1] = 0;
		for(int d = 0; d <= 9; ++d) {
			if(d == 4) continue;
			for(int k : {0, 1}) {
				if(k && d > s[i-1]-'0') continue;
				dp[i][k && d == s[i - 1] - '0'] += dp[i - 1][k];
			}
		}
	}	
	return dp[s.size()][0] + dp[s.size()][1];
}

void solve() {
	i64 k;
	cin >> k;
	++k;
	i64 lo = 1, hi = 1e18L;
	while(lo < hi) {
		i64 m = (lo + hi) / 2;
		if(count_numbers(m) >= k) hi = m;
		else lo = m + 1;
	}
	cout << hi << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
