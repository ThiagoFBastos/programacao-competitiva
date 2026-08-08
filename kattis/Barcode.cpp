#pragma GCC optimize("O3")
#pragma GCC target("mmx,sse,sse2,sse3,sse4")

#include "bits/stdc++.h"

using namespace std;

const int N = 1e6 + 1;
using ll = long long;

int fib[N], fat[N], inv[N], inv_fat[N];

int C(int n, int k, int p) {
	return 1LL * fat[n] * inv_fat[k] % p * inv_fat[n - k] % p;
}

int mod_sum(int x, int y) {
	return x >= y ? x - y : x;
}

void solve() {
	int n, p;
	cin >> n >> p;
	
	for(int k = 0; k < 2; ++k) {
		fat[k] = inv[k] = inv_fat[k] = 1;
		fib[k] = (k + 1) % p;
	}
	
	for(int k = 2; k <= n; ++k) {
		fib[k] = mod_sum(fib[k - 1] + fib[k - 2], p);
		fat[k] = 1LL * fat[k - 1] * k % p;
		inv[k] = -(p / k + 0LL) * inv[p % k] % p;
		inv_fat[k] = 1LL * inv[k] * inv_fat[k - 1] % p;
	}
	
	if(n & 1) cout << fib[n] << '\n';
	else {
		int c = 1, x = n, y = n / 2;
		while(y > 0) {
			int a = x % p, b = y % p;
			if(a < b) {
				c = 0;
				break;
			}
			c = 1LL * c * C(a, b, p) % p;
			x /= p;
			y /= p;
		}
		cout << ((1LL * c + 1LL * fib[n] - n / 2 - 1) % p + p) % p << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}