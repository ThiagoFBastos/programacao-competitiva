#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int MOD = 1e9 + 7;

i64 exp(i64 n, int p, int mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

i64 sum_squares(i64 n) {
	return n * (2ll * n + 1) % MOD * (n + 1) % MOD * exp(6, MOD - 2, MOD) % MOD;
}

i64 sum_linear(i64 n) {
	return n * (n + 1ll) % MOD * exp(2, MOD - 2, MOD) % MOD;
}

void solve() {
	int n;
	cin >> n;
	i64 ans = (2 * sum_squares(n) - sum_linear(n)) % MOD * 2022 % MOD;
	cout << (ans + MOD) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

