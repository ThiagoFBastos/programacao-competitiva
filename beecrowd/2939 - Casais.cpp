#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int MOD = 1e9 + 7;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, f1, f2;
	cin >> n;
	f1 = 1;
	f2 = 2 * n;
	for(int k = 2; k <= n; ++k) {
		int r = (2LL * (n - k + 1) * f2 + (n - k + 2LL) * (n - k + 1LL) % MOD * f1 * 4LL) % MOD;
		f1 = f2;
		f2 = r;
	}
	cout << f2 << '\n';
    return 0;
}