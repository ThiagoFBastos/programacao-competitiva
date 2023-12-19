#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
long long exp(long long n, long long p) {
	long long a = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) a = a * n % mod;
		n = n * n % mod;
	}
	return a;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	if(n == 1) cout << "2\n";
	else {
		long long x = exp(2, 1LL * n * n);
		long long y = exp(2, 1LL * n * n / 4) * (n % 2 + 1);
		long long z = (exp(2, 1LL * n * n / 2) * (n % 2 + 1) - y) % mod;
		long long ans = ((x - y - z) * exp(4, mod - 2) + z * exp(2, mod - 2) + y) % mod;
		cout << (ans + mod) % mod << '\n';
	}	
	return 0;
}
