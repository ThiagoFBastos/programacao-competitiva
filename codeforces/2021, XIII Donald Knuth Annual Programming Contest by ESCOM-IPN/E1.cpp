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

int dp[1 << 20], n;

int DP(int mask) {
	if(dp[mask] != -1) return dp[mask];
	int k = __builtin_popcount(mask);
	return dp[mask] = 1 + DP(mask ^ (1 << (k - 1)));
}

void solve() {
	i64 a = 0;

	cin >> n;

	memset(dp, -1, sizeof(int) << n);
	dp[0] = 0;

	for(int i = 0; i < (1 << n); ++i) a += DP(i);

	i64 g = gcd(1<<n, a);

	cout<<a/g<<'/'<<(1<<n)/g<<'\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

