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

void solve() {
	int n;

	cin >> n;

	const int MOD = 1e9 + 7;
	map<int, int> cur;
	vector<int> dp(n + 1);
	int last = -1;

	dp[0] = 1;

	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		if(last != a) dp[i] = dp[i - 1] + cur[a];
		else dp[i] = dp[i - 1];
		if(dp[i] >= MOD) dp[i] -= MOD;
		cur[a] = dp[i];
		last = a;
	}

	cout << dp[n] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
