#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
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

const int N = 1e6 + 10, MOD = 998'244'353;

bitset<N> is_prime;
int d[N], primes[N], np;
i64 fac[N];

void solve() {
	i64 l, r, ans = 0;
	int k;

	cin >> l >> r >> k;

	for(int i = 0; i < r - l + 1; ++i) {
		d[i] = 1;
		fac[i] = l + i;
	}

	for(int j = 0; j < np; ++j) {
		int p = primes[j];
		if((i64)p * p > r) break;
		for(i64 i = (p - l % p) % p + l; i <= r; i += p) {
			int j = 0;
			i64& f = fac[i - l];
			while(f >= p && f % p == 0) {
				f /= p;
				j += k;
			}
			d[i - l] = (1ll + j) * d[i - l] % MOD;
		}
	}

	for(int i = 0; i < r - l + 1; ++i) {
		if(fac[i] != 1) d[i] = (1ll + k) * d[i] % MOD;
		ans += d[i];
	}
	
	cout << ans % MOD << '\n';
}

int main() {
	is_prime.set();
	for(int p = 2; p * p < N; ++p) {
		if(!is_prime[p]) continue;
		for(int i = p * p; i < N; i += p) is_prime[i] = 0;
	}
	for(int i = 2; i < N; ++i) if(is_prime[i]) primes[np++] = i;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}