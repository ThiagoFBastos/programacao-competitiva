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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 14001;

int primes[N];

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> dp(1 << n, 0), soma(1 << n, 0), a(n);
	
	for(int& v : a) cin >> v;
	
	for(int i = 1; i < (1 << n); ++i) soma[i] = soma[i - (i & -i)] + a[__builtin_ctz(i & -i)];
	
	for(int i = (1 << n) - 1; i > 0; --i)
		for(int k = i; k; k = (k - 1) & i)
			dp[i ^ k] = max(dp[i ^ k], dp[i] + primes[soma[k]]);
	
	cout << dp[0] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	for(int k = 2; k < N; ++k) {
		if(primes[k]) continue;
		for(int i = k; i < N; i += k) ++primes[i];
	}
	
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
