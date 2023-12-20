#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 125250
#define MOD 1000000007
int expmod(int n, int p) {
	if(p == 0) return 1;
	int r = expmod(n, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * r * n % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int dp[MAXN + 1], n;
	cin >> n;
	int N = n * (n + 1) / 2 + 1;
	if(N - 1 & 1)
		cout << 0 << '\n';
	else {
		memset(dp, 0, sizeof(int) * N);
		dp[0] = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = N - 1; j >= i; --j)
				dp[j] = (dp[j] + dp[j - i]) % MOD;
		cout << 1LL * dp[(N - 1) / 2] * expmod(2, MOD - 2) % MOD << '\n';
	}
	return 0;
} 
