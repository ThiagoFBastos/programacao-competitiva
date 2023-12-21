#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	sort(a.begin(), a.end());
	long long s, ans = -1;
	if(a[0] != 1) ans = 1;
	else {
		s = 1;
		for(int i = 1; i < n; ++i) {
			if(s + 1 < a[i]) {
				ans = s + 1;
				break;
			} else s += a[i];
		}
		if(ans == -1) ans = s + 1;
	}
	cout << ans << '\n';
	return 0;
}
