#pragma GCC target("popcnt,mmx,sse,sse2,sse3,avx,avx2")
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
//using i128 = __int128;

const int N = 20;

int t[N], d[N][N], dp[1<<N][N], n;

void solve() {
	while(true) {
		int ans = 0;

		cin >> n;

		if(!n) break;

		for(int i = 0; i < n; ++i) cin >> t[i];

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				cin >> d[i][j];

		for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		for(int i = 0; i < n; ++i) {
			dp[1<<i][i] = t[i];
			if(t[i] <= 420) ans = 1;
		}
	
		for(int i = 1; i < (1 << n); ++i) {
			int l = __builtin_popcount(i);
			if(l == 1) continue;
			for(int A = i; A; A -= A & -A) {
				int j = __builtin_ctz(A), c = INF;
				for(int B = i ^ (1 << j); B; B -= B & -B) {
					int k = __builtin_ctz(B);
					c = min(c, dp[i^(1<<j)][k] + d[k][j]);
				}
				dp[i][j] = c + t[j];
				if(dp[i][j] <= 420) ans = max(ans, l);
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