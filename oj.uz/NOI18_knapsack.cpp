#include "bits/stdc++.h"

using namespace std;

#define INF 2000000100
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

const int N = 2e3 + 100;

int dp[N], lo[N], hi[N];

ii dq[N][N];

void solve() {
int s, n;

cin >> s >> n;

fill(dp, dp + N, -INF);

dp[0] = 0;

for(int i = 0; i < n; ++i) {
	int v, w, c;

	cin >> v >> w >> c;

	c = min(c, s / w);

	
	for(int k = 0; k < w; ++k) lo[k] = hi[k] = 0;

	for(int k = 0, mod = 0, j = 0; k <= s; ++k) {
		int X = dp[k];
		
		while(lo[mod] < hi[mod] && j - dq[mod][lo[mod]].sc > c) ++lo[mod];

		if(lo[mod] != hi[mod]) dp[k] = max(dp[k], dq[mod][lo[mod]].fi + v * j);

		if(X >= 0) {
			while(lo[mod] < hi[mod] && dq[mod][hi[mod] - 1].fi < X - v * j) --hi[mod];
			dq[mod][hi[mod]++] = {X - v * j, j};
		}

		if(++mod == w) mod = 0, ++j;
	}
}

cout << *max_element(dp, dp + N) << '\n';
}	

int main() {
ios_base :: sync_with_stdio(false);
cin.tie(0);
int t = 1;
//	cin >> t;
while(t--) solve();
return 0;
}
