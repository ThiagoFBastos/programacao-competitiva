#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, maxn = 0;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		maxn = max(maxn, a[i]);
	}
	vector<bool> p(maxn + 1, false);
	vector<int> k(maxn + 1, -1), cnt(maxn + 1, 0);
	for(int x : a) ++cnt[x];
	long long ans = n * (n - 1LL) / 2;
	for(int i = 2; i <= maxn; ++i) {
		if(!p[i]) {
			for(int j = i; j <= maxn; j += i) p[j] = true, k[j] = -k[j];
			if(1LL * i * i <= maxn) for(int j = i * i; j <= maxn; j += i * i) k[j] = 0;
		}
		if(k[i]) {
			int t = 0;
			for(int j = i; j <= maxn; j += i) t += cnt[j];
			ans -= t * (t - 1LL) / 2 * k[i];
		}
	}
	cout << ans << '\n';
	return 0;
}
