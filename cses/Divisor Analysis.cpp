#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
long long exp(long long n, long long k) {
	long long ans = 1;
	for(; k > 0; k >>= 1) {
		if(k & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>> a(n);
	vector<int> pre(n + 1), suf(n + 2);
	int x = 1, y = 1, z = 1, w = 1;
	for(int i = 0; i < n; ++i) {
		cin >> a[i].first >> a[i].second;
		x = x * (a[i].second + 1LL) % mod;
		y = y * (exp(a[i].first, a[i].second + 1) - 1) % mod * exp(a[i].first - 1, mod - 2) % mod;
	}
	pre[0] = suf[n] = 1;
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * (a[i - 1].second + 1LL) % (mod - 1);
	for(int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] * (a[i].second + 1LL) % (mod - 1);
	if(y < 0) y += mod;
	for(int i = 0; i < n; ++i) z = z * exp(a[i].first, a[i].second * (a[i].second + 1LL) / 2 % (mod - 1) * pre[i] % (mod - 1) * suf[i + 1] % (mod - 1)) % mod;
	cout << x << ' ' << y << ' ' << z << '\n';
	return 0;
}
