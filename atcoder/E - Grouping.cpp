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

const int N = 1e3 + 10, MOD = 1e9 + 7;

int dp[N], fat[N], inv[N], invf[N], invf_pw[N][N];

int comb(int n, int k) {
	return 1ll * fat[n] * invf[n - k] % MOD * invf[k] % MOD;
}

int f(int n, int a, int i) {
	return 1ll * fat[a * i] * invf_pw[a][i] % MOD * invf[i] % MOD * comb(n, a * i) % MOD; 
}

void solve() {
	int n, a, b, c, d;

	cin >> n >> a >> b >> c >> d;
	
	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= n; ++i) {
		fat[i] = 1ll * i * fat[i - 1] % MOD;
		inv[i] = (MOD - MOD / i + 0ll) * inv[MOD % i] % MOD;
		invf[i] = 1ll * inv[i] * invf[i - 1] % MOD;
	}

	for(int i = 0; i <= n; ++i) {
		invf_pw[i][0] = 1;
		for(int j = 1; j <= n; ++j) invf_pw[i][j] = 1ll * invf_pw[i][j - 1] * invf[i] % MOD;
	}
	
	dp[0] = 1;
		
	for(; a <= b; ++a)
		for(int k = n - a; k >= 0; --k)
			for(int i = c; i <= d && k + i * a <= n; ++i)
				dp[k + i * a] = (dp[k + i * a] + 1ll * f(n - k, a, i) * dp[k]) % MOD;

	cout << dp[n] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
