#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		long long f = 1, step = 1, x = -1;
		while(n > 0) {
			if(k <= n / 2) {
				x = f + step + 2 * (k - 1) * step;
				break;
			} else if(n & 1) {
				k -= (n + 1) / 2;
				if(k == 0) {
					x = f;
					break;
				}
				f += step << 1;
				--n;
			} else k -= n / 2;
			n >>= 1;
			step <<= 1;
		}
		cout << x << '\n';
	}
	return 0;
}
