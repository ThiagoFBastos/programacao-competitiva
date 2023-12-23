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

void solve() {
	int n;

	cin >> n;

	vector<int> a(n);
	vector<char> op(n, '+');
	vector<i64> abs_sum(n + 1, 0), dp(n + 1);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		if(i + 1 < n) cin >> op[i + 1];
		abs_sum[i + 1] = abs_sum[i] + a[i];
	}

	dp[n] = 0;

	int hi = n;

	for(int i = n - 1; i >= 0; --i) {
		if(op[i] == '+') dp[i] = dp[i + 1] + a[i];			
		else {
			i64 s = abs_sum[n] - 2 * abs_sum[hi] + abs_sum[i];
			dp[i] = max(s, dp[i + 1] - a[i]);
			hi = i;
		}
	}

	cout << dp[0] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
