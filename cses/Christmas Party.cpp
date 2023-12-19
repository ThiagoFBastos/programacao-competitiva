#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int MOD = 1e9 + 7;
int expmod(int n, int p) {
	if(!p) return 1;
	int r = expmod(n, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * n * r % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, *f, ans = 0;
	cin >> n;
	f = new int[n + 1];
	f[0] = 1;
	for(int k = 1; k <= n; ++k) f[k] = 1LL * f[k - 1] * k % MOD;
	ans = f[n];
	for(int k = 1; k <= n; ++k) ans = (ans - 1LL * ((k & 1) - (k + 1 & 1)) * f[n] * expmod(f[k], MOD - 2)) % MOD; 
	cout << (ans + MOD) % MOD << '\n';
    return 0;
} 
