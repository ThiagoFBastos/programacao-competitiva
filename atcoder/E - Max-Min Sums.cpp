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


const int N = 1e5 + 1, mod = 1e9 + 7;

i64 fat[N], inv[N], invFat[N];

i64 C(int n, int k) {
	return fat[n] * invFat[k] % mod * invFat[n - k] % mod;
}

void solve() {
	int n, k;

	cin >> n >> k;

	vector<int> a(n);

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invFat[i] = 1;
	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = -(mod / i) * inv[mod % i] % mod;
		invFat[i] = invFat[i - 1] * inv[i] % mod;
	}

	for(int& v : a) cin >> v;

	sort(a.begin(), a.end());

	i64 ans = 0;

	for(int i = k - 1; i < n; ++i) ans = (ans + a[i] * C(i, k - 1)) % mod;
	for(int i = 0; i <= n - k; ++i) ans = (ans - a[i] * C(n - i - 1, k - 1)) % mod;

	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

