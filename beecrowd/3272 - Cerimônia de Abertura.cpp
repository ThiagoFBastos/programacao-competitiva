#include "bits/stdc++.h"
using namespace std;
const int maxn = 1e6 + 1;
int cnt[maxn];
void solve() {
	int n, res1 = 0, res2 = INT_MAX, H = 0;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		int h;
		cin >> h;
		++cnt[h];
		H = max(H, h);
	}
	for(int k = H; k > 0; --k) {
		if(!cnt[k]) continue;
		else if(cnt[k] >= k) {
			++res1;
			cnt[k - 1] += cnt[k];
		} else {
			res2 = min(res2, res1 + k);
			res1 += cnt[k];
		}
	}
	cout << min(res1, res2) << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}