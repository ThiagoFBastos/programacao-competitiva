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

const int mod = 998244353, N = 64, M = 2600;

i64 dp[2][N][N], fat[M], invf[M], inv[M];

i64 C(int n, int k) {
	return fat[n] * invf[n - k] % mod * invf[k] % mod;
}

void solve() {
	
	int n, m, b, w;

	cin >> n >> m >> b >> w;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= n * m; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}

	for(int n0 = 1; n0 <= n; ++n0) {
		for(int m0 = 1; m0 <= m; ++m0) {
			if(n0 * m0 >= b) dp[0][n0][m0] = C(n0 * m0, b);
			if(n0 * m0 >= w) dp[1][n0][m0] = C(n0 * m0, w);
		}
	}

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			for(int _i = i; _i <= n; ++_i) {
				for(int _j = 1; _j <= m; ++_j) {
					if(_i == i && _j == j) continue;
					for(int k = 0; k < 2; ++k) {
						i64 X = dp[k][i][j] * C(_i, i) % mod * C(_j, j) % mod;
						dp[k][_i][_j] -= X;
						if(dp[k][_i][_j] < 0) dp[k][_i][_j] += mod;
					}
				}
			}
		}
	}

	i64 ans = 0;

	for(int n0 = 1; n0 <= n; ++n0) {
		for(int m0 = 1; m0 <= m; ++m0) {
			if(n0 * m0 < b) continue;
			for(int n1 = 1; n1 <= n - n0; ++n1) {
				for(int m1 = 1; m1 <= m - m0; ++m1) {
					if(n1 * m1 < w) continue;
					i64 X = C(n, n0) * C(m, m0) % mod * C(n - n0, n1) % mod * C(m - m0, m1) % mod;
					X = X * dp[0][n0][m0] % mod * dp[1][n1][m1] % mod;
					ans = (ans + X) % mod;
				}
			}
		}
	}

	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
