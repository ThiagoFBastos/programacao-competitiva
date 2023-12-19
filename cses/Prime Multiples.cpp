#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long n;
	int k;
	cin >> n >> k;
	vector<long long> p(k);
	for(int i = 0; i < k; ++i) cin >> p[i]; 
	long long ans = 0;
	for(int i = 1; i < (1 << k); ++i) {
		long long x = 1;
		int cnt = -1;
		for(int j = 0; j < k; ++j) {
			if(1 << j & i) {
				cnt = -cnt;
				if(p[j] > n / x) {
					x = -1;
					break;
				}
				x *= p[j];
			}
		}
		if(x != -1) ans += n / x * cnt;
	}
	cout << ans << '\n';
	return 0;
}
