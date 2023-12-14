#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
int n, k;
vector<long long> fac, inv, inv_fac;
long long C(int a, int b) {
	return fac[a] * inv_fac[b] % mod * inv_fac[a - b] % mod;	
}
long long exp(long long a, long long b) {
	long long c = 1;
	for(; b > 0; b >>= 1) {
		if(b & 1) c = c * a % mod;
		a = a * a % mod;
	}
	return c;
}
int solve() {
	int ans = exp(n, k);
	fac.resize(n + 1);
	inv.resize(n + 1);
	inv_fac.resize(n + 1);
	fac[0] = fac[1] = inv[1] = inv_fac[1] = inv_fac[0] = 1;
	inv[0] = 0;
	for(int i = 2; i <= n; ++i) {
		fac[i] = i * fac[i - 1] % mod;
		inv[i] = -(mod / i) * inv[mod % i] % mod;
		inv_fac[i] = inv_fac[i - 1] * inv[i] % mod;
	}
	for(int i = 1; i < n; ++i) ans = (ans + (i & 1 ? -1 : 1) * exp(n - i, k) * C(n, i)) % mod;
	if(ans < 0) ans += mod;
	return ans;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> k >> n;
	cout << solve() << '\n';
	return 0;
}
