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

const int N = 2e5 + 100, MOD = 1e9 + 7;

i64 fat[N], inv[N], invf[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}

void solve() {
	int h, w, a, b;

	cin >> h >> w >> a >> b;

	for(int i = 0; i <= h + w; ++i) {
		fat[i] = i < 2 ? 1 : i * fat[i - 1] % MOD;
		inv[i] = i < 2 ? 1 : (MOD - MOD / i) * inv[MOD % i] % MOD;
		invf[i] = i < 2 ? 1 : inv[i] * invf[i - 1] % MOD;
	}

	i64 ans = 0;

	for(int r = 1; r < h - a + 1; ++r) {
		i64 cnt = C(r + b - 2, r - 1) * C(h + w - (r + b + 1), h - r) % MOD;
		ans = (ans + cnt) % MOD;	
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
