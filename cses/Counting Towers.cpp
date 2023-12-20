#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 1, mod = 1e9 + 7;
int x[N], y[N];
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	x[1] = 1, y[1] = 1;
	for(int i = 2; i < N; ++i) {
		x[i] = (2LL * x[i - 1] + y[i - 1]) % mod;
		y[i] = (x[i - 1] + 4LL * y[i - 1]) % mod;
	}
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		cout << (x[n] + y[n]) % mod << '\n';
	}
	return 0;
}
