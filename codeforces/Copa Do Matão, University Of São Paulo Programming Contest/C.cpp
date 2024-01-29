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

const int mod = 1e9 + 7;

void solve() {
	int n, k;

	cin >> n >> k;

	vector<i64> a(max(n, k) + 1);

	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	i64 P = a[1], Q = -a[1];

	for(int i = 2; i <= n; ++i) {
		a[i] = min(a[i], P * i + Q);
		P += a[i];
		Q += -(i64)i * a[i];
	}
	
	P = Q = 0;

	for(int i = 1; i <= n; ++i) {
		P = (P + a[i]) % mod;
		Q = (Q + -i * a[i]) % mod;
	}

	for(int i = n + 1; i <= k; ++i) {
		a[i] = (Q + (i64)i * P) % mod;
		P = (P + a[i]) % mod;
		Q = (Q + -i * a[i]) % mod;
	}

	cout << (a[k] + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


