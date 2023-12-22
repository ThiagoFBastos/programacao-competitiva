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

const int N = 54773;

i64 dp[N];

void solve() {
	i64 s = 0;
	int hi = 1;	
  
	dp[1] = 1;
  
	for(int i = 2; i < N; ++i) {
		while(hi * hi <= i) s += dp[hi++];
		dp[i] = s;
	}
  
	int q;

	cin >> q;

	while(q--) {
		i64 X;

		cin >> X;

		if(X < N) {
			cout << dp[X] << '\n';
			continue;
		}

		i64 ans = 0;

		for(int i = 1; i < N; ++i) if((i64)i * i <= X) ans += dp[i];
		
		for(int i = 1; i < N; ++i) {
			if((i64)i * i * i * i <= X) {
				i64 l = max(N + 0ll, (i64)i * i);
				i64 r = sqrt(X + 0.0L);
				ans += max(0ll, r - l + 1) * dp[i];
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
