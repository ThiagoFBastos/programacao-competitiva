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

const int MOD = 1e9 + 7, N = 2e6 + 10;

i64 fat[N], inv[N], invf[N];

i64 C(int n, int k) {
	return fat[n] * invf[n - k] % MOD * invf[k] % MOD; 
}

void solve() {
	int n, m, k;

	cin >> n >> m >> k;

	for(int i : {0,1}) fat[i] = inv[i] = invf[i] = 1;
	
	for(int i = 2; i <= n + m; ++i) {
		fat[i] = i * fat[i - 1] % MOD;
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
		invf[i] = inv[i] * invf[i - 1] % MOD;
	}


	if(n - m > k) {
		cout << "0\n";
		return;
	}

	if(k == n) {
		cout << C(n + m, n) << '\n';
		return;
	}
	
	cout << (C(n+m,n)-C(n+m,n-k-1)+MOD)%MOD<<'\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
