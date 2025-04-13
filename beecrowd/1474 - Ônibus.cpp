#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
const int N = 10, MOD = 1e6;
void mult(ll a[N][N], ll b[N][N]) {
	ll c[N][N];
	for(int k = 0; k < N; ++k) {
		for(int i = 0; i < N; ++i) {
			c[k][i] = 0;
			for(int j = 0; j < N; ++j)
				c[k][i] += a[k][j] * b[j][i];
		}
	}
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			a[i][j] = c[i][j] % MOD;
}
void matrix_power(ll ans[N][N], ll dp[N][N], ll p) {
	for(int k = 0; k < N; ++k)
		for(int i = 0; i < N; ++i)
			ans[k][i] = k == i;
	while(p) {
		if(p & 1) mult(ans, dp);
		mult(dp, dp);
		p >>= 1;
	}
}
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	ll n, k, l, f[N + 1], dp[N][N], ans[N][N];
	while(cin >> n >> k >> l) {
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < N; ++j)
				dp[i][j] = 0;
		k %= MOD;
		l %= MOD;
		dp[9][0] = l;
		dp[9][5] = k;
		for(int i = 0; i < N - 1; ++i) 
			dp[i][i + 1] = 1;
		f[0] = 1;
		for(int i = 1; i <= N; ++i) {
			f[i] = 0;
			if(i - 5 >= 0) 
				f[i] = k * f[i - 5] % MOD;
			if(i - 10 >= 0) 
				f[i] = (f[i] + l * f[i - 10]) % MOD;
		}
		if(n == 5) cout << setw(6) << setfill('0') << f[5] << '\n';
		else if(n == 10) cout << setw(6) << setfill('0') << f[10] << '\n';
		else {
			ll res = 0;
			matrix_power(ans, dp, n - 10);
			for(int k = 0; k < N; ++k)
				res = (res + f[k + 1] * ans[9][k]) % MOD;
			cout << setw(6) << setfill('0') << res << '\n';
		}
	}
	return 0;
}