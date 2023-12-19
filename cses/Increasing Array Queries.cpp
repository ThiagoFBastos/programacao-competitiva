#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	vector<long long> p(n + 1), ans(q);
	p[0] = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i - 1];
		p[i] = a[i - 1] + p[i - 1];
	}
	vector<vector<pair<int, int>>> Q(n);
	for(int i = 0; i < q; ++i) {
		int L, R;
		cin >> L >> R;
		Q[L - 1].push_back({R, i});
	}
	vector<int> x(n + 1, INT_MIN), cnt(n + 1), last(n + 1);
	vector<long long> suf(n + 1);
	int j = n;
	x[n] = INT_MAX, last[n] = n, suf[n] = 0, cnt[n] = 0;
	for(int k = n - 1; k >= 0; --k) {
		int i = upper_bound(x.begin() + j, x.end(), a[k]) - x.begin() - 1;
		cnt[i] = last[i + 1] - k + cnt[i + 1], suf[i] = suf[i + 1] + (0LL + last[i + 1] - k) * a[k], last[i] = k, x[i] = a[k];
		j = i;
		for(auto [R, j] : Q[k]) {
			int lo = i, hi = n - 1;
			while(lo < hi) {
				int mid = (lo + hi) / 2;
				if(cnt[i] - cnt[mid + 1] >= R - k) hi = mid;
				else lo = mid + 1;
			}
			ans[j] = suf[i] - suf[hi + 1] - (cnt[i] - cnt[hi + 1] - R + k + 0LL) * x[hi] - p[R] + p[k]; 
		}
	}
	for(auto& x : ans) cout << x << '\n';
	return 0;
}
