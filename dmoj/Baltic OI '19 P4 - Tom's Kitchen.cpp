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

const int N = 90001;

array<int, N> dp;

void solve() {
	int n, m, k;

	cin >> n >> m >> k;

	int s = 0;
	
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		if(a < k) {
			cout << "Impossible\n";
			return;
		}
		s += a;
	}
	
	fill(all(dp), -INF);

	dp[0] = 0;

	for(int i = 0; i < m; ++i) {
		int b;
		cin >> b;
		for(int j = N - b - 1; j >= 0; --j)
			dp[b + j] = max(dp[b + j], dp[j] + min(n, b)); 
	}

	int ans = INF;

	for(int i = s; i < N; ++i) if(dp[i] >= k * n) ans = min(ans, i - s);
	
	if(ans == INF) cout << "Impossible\n";
	else cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
