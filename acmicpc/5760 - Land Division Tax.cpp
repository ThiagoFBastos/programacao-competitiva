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

const int N = 2e2 + 10;

int dp[N][N], ps[N], n;
double f;

int query(int l, int r) {
	if(l <= r) return ps[r+1]-ps[l];
	return ps[r+1] + ps[n]-ps[l];
}

void solve() {
	while(true) {
		cin >> n >> f;

		if(!n) break;

		for(int i = 1; i <= n; ++i) {
			cin >> ps[i];
			ps[i] += ps[i - 1];
		}

		for(int i = 0; i < n; ++i) dp[i][i] = 0;

		for(int len = 2; len <= n; ++len) {
			for(int l = 0; l < n; ++l) {
				int r = (l + len - 1) % n;
				dp[l][r] = INF;
				for(int i = 0; i < len - 1; ++i) {
					int C = dp[l][(i+l)%n] + dp[(i+l+1)%n][r] + max(query(l,(i+l)%n),query((i+l+1)%n,r));
					dp[l][r] = min(dp[l][r], C);
				}
			}
		}

		cout.precision(2);
		cout.setf(ios_base :: fixed);
		
		int best = INF;
		for(int i = 0; i < n; ++i) best = min(best, dp[i][(i+n-1)%n]);
	
		cout << best * f << '\n';
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
