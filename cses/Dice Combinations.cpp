#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MOD 1000000007LL
#define MAXN 6
void mult(ll a[MAXN][MAXN], ll b[MAXN][MAXN]) {
	ll c[MAXN][MAXN];
	for(int i = 0; i < 6; ++i) {
		for(int j = 0; j < 6; ++j) {
			ll r = 0;
			for(int k = 0; k < 6; ++k)
				r += a[i][k] * b[k][j];
			c[i][j] = r % MOD;
		}
	}
	for(int i = 0; i < 6; ++i)
		for(int j = 0; j < 6; ++j)
			a[i][j] = c[i][j];
}
void matrix_pow(ll a[MAXN][MAXN], ll b[MAXN][MAXN], ll p) {
	if(p == 0) {
		for(int i = 0; i < 6; ++i)
			for(int j = 0; j < 6; ++j)
				a[i][j] = i == j;
	}
	else {
		matrix_pow(a, b, p >> 1);
		mult(a, a);
		if(p & 1) mult(a, b);
	}
} 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n;
	int dp[7] = {0};
	dp[0] = 1;
	for(int i = 1; i <= 6; ++i)
		for(int j = 1; j <= 6 && i - j >= 0; ++j)
			dp[i] += dp[i - j];
	cin >> n;
	if(n < 7) cout << dp[n] << '\n';
	else {
		ll m[MAXN][MAXN], b[MAXN][MAXN];
		for(int i = 0; i < 6; ++i)
			for(int j = 0; j < 6; ++j)
				m[i][j] = 0;
		for(int i = 0; i < 6; ++i)
			m[0][i] = 1;
		for(int i = 1; i < 6; ++i)
			m[i][i - 1] = 1;
		matrix_pow(b, m, n - 6);
		ll ans = 0;
		for(int k = 1; k <= 6; ++k)
			ans += dp[7 - k] * b[0][k - 1];
		cout << ans % MOD << '\n'; 
	}
	return 0;
} 
