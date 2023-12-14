#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> cnt(n * (n - 1) / 2 + 1, 0);
	cnt[0] = 1;
	for(int i = 0; i < n; ++i) {
		vector<int> p(cnt.size(), 0);
		for(int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
			p[j] += cnt[j];
			p[j + i + 1] -= cnt[j];
			if(p[j] >= mod) p[j] -= mod;
			if(p[j + i + 1] < 0) p[j + i + 1] += mod;
		}
		for(int j = 1; j <= (i + 1) * i / 2; ++j) {
			if(j > k) p[j] = 0;
			else {
				p[j] += p[j - 1];
				if(p[j] >= mod) p[j] -= mod;
			}
		}
		copy(p.begin(), p.end(), cnt.begin());
	}
	cout << cnt[k] << '\n';
	return 0;
}
