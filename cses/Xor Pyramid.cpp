#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		ans ^= x;
		for(int k = 0; (1 << k) <= n - 1; ++k) {
			if(((n - 1) & 1 << k) < (i & 1 << k)) {
				ans ^= x;
				break;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
