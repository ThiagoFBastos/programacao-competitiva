#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 64, mod = 998244353;

i64 fat[N], inv[N], invf[N];

array<array<i64, N>, N> dp[2];

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void solve() {

	int n, m, k;

	cin >> n >> m >> k;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= k; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = inv[i] * invf[i - 1] % mod;
	}

	vector<int> w(n);
	int s = 0;

	for(int& v : w) {
		cin >> v;
		s += v;
	}

	for(int i = 0; i <= k; ++i)
	for(int j = 0; j <= m; ++j)
		 dp[0][i][j] = 0;

	dp[0][0][0] = 1;

	for(int l = 0; l < n; ++l) {
		dp[1] = dp[0];		
		i64 p = w[l] * exp(s, mod - 2) % mod, b = 1;
		for(int q = 1; q <= k; ++q) {
			b = p * b % mod;
			for(int i = 0; i + q <= k; ++i) {
				for(int j = 0; j < m; ++j) { 
					i64 C = fat[i + q] * invf[i] % mod * invf[q] % mod;
					i64 X = dp[0][i][j] * C % mod * b % mod;
					dp[1][i + q][j + 1] = (dp[1][i + q][j + 1] + X) % mod;
				}
			}
		}
		swap(dp[0], dp[1]);
	}

	cout << dp[0][k][m] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
