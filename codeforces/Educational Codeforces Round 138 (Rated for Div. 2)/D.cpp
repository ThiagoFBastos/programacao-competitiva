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

const int MOD = 998244353, N = 3e5 + 100;

bitset<N> is_prime;

void solve() {

	int n;
	i64 m;

	cin >> n >> m;

	i64 dp[2];
	
	dp[0] = m % MOD;
	dp[1] = 0;

	i64 L = 1, ans = 0;

	is_prime.set();
	for(int p = 2; p * p <= n; ++p) {
		if(!is_prime[p]) continue;
		for(int k = 2 * p; k <= n; k += p) is_prime[k] = 0;
	}

	for(int k = 2; k <= n; ++k) {
		if(is_prime[k]) L = min((__int128)L / gcd(k, L) * k, (__int128)m + 1);
		dp[1] = (m % MOD * dp[1] + (m - m / L) % MOD * dp[0]) % MOD;
		dp[0] = (m / L) % MOD * dp[0] % MOD;
		ans = (ans + dp[1]) % MOD;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	//cin >> t;
	while(t--) solve();
	return 0;
}
