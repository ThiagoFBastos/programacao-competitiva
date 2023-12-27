#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x[20];
	cin >> n;
	int N = 1 << n;
	ll *dp = new ll[N];
	dp[N - 1] = 0;
	for(int k = 0; k < n; ++k) {
		cin >> x[k];
		dp[N - 1] += x[k];
	}
	ll minsum = dp[N - 1];
	for(int k = N - 2; k > 0; --k) {
		int p = ~k & -(~k);
		dp[k] = dp[k | p] - x[__builtin_ctzll(p)];
		minsum = min(minsum, llabs(dp[N - 1] - 2 * dp[k]));
	}
	cout << minsum << '\n';
	return 0;
} 
