#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

const int N = 1e6 + 10, MOD = 998244353;

i64 factors(i64 n, int p) {
	i64 ans = 0;
	while(n > 0) {
		ans += n /= p;
		ans %= MOD;
	}
	return ans;
}

bitset<N> is_prime;
i64 fact[N];

void solve() {
	i64 n;
	int k;
	cin >> n >> k;

	i64 lo = n - k + 1;
	for(int i = 0; i < k; ++i) fact[i] = lo + i;

	is_prime.set();
	for(int p = 2; p * p < N; ++p) {
		if(!is_prime[p]) continue;
		for(int i = p * p; i < N; i += p) is_prime[i] = 0;
	}

	i64 cnt = 1;

	for(int p = 2; p < N; ++p) {
		if(!is_prime[p]) continue;
		i64 l = lo + (p-lo%p) % p;
		cnt = cnt * (factors(n,p) - factors(lo-1,p) - factors(k,p) + 1) % MOD;
		for(; l <= n; l += p) while(fact[l - lo] % p == 0) fact[l - lo] /= p;	
	}

	for(i64 i = lo; i <= n; ++i) cnt = cnt * ((fact[i - lo] != 1) + 1) % MOD;

	cout << (cnt+MOD) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
