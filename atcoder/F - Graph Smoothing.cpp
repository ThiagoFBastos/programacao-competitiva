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

const int N = 100, mod = 1e9 + 7;

int n, m, k, g[N][N], a[N], deg[N];
i64 t[N][N], q[N][N];

i64 exp(i64 n, int p, int mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void mul(i64 a[][N], i64 b[][N]) {
	i64 c[N][N];
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			c[i][j] = 0;
			for(int k = 0; k < n; ++k)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
		}
	}
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		a[i][j] = c[i][j];
}

void expmod(i64 dest[][N], i64 src[][N], int p) {
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		dest[i][j] = i == j;		
	for(; p > 0; p >>= 1) {
		if(p & 1) mul(dest, src);
		mul(src, src);
	}
}

void solve() {
	cin >> n >> m >> k;

	for(int i = 0; i < n; ++i) cin >> a[i];

	for(int k = 0; k < m; ++k) {
		int i, j;
		cin >> i >> j;
		--i, --j;
		g[i][j] = g[j][i] = 1;
		++deg[i], ++deg[j];
	}

	i64 X = exp(m, mod - 2, mod);
	i64 Y = exp(2, mod - 2, mod);

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i == j) t[i][i] = ((m - deg[i]) * X + deg[i] * X % mod * Y) % mod;
			else t[i][j] = g[i][j] * X * Y % mod;
		}
	}

	expmod(q, t, k);

	for(int i = 0; i < n; ++i) {
		i64 v = 0;
		for(int k = 0; k < n; ++k) v = (v + a[k] * q[k][i]) % mod;
		cout << v << '\n';
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

