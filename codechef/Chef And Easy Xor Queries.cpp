#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, q;
	cin >> n >> q;
	int sz = sqrt(n) + 1;
	int m = (n + sz - 1) / sz;
	vector<int> a(n), val(m, 0);
	vector<vector<int>> S(m);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		int k = i / sz;
		val[k] ^= a[i];
		if(S[k].empty()) S[k].push_back(a[i]);
		else S[k].push_back(S[k].back() ^ a[i]);
	}
	for(int i = 0; i < m; ++i) {
		if(!S[i].empty()) S[i].pop_back();
		sort(S[i].begin(), S[i].end());
	}
	while(q--) {
		int t, i, x, k;
		cin >> t >> i >> x;
		k = --i / sz;
		if(t == 1) {
			int v = 0;
			val[k] ^= x ^ a[i];
			a[i] = x;
			for(int l = k * sz, j = 0; l < min(n, (k + 1) * sz - 1); ++j, ++l) v = S[k][j] = v ^ a[l];
			sort(S[k].begin(), S[k].end());
		} else {
			int cnt = 0, v = 0;
			for(int j = 0; j < k - 1; ++j) {
				v ^= val[j];
				if(v == x) ++cnt;
				cnt += upper_bound(S[j + 1].begin(), S[j + 1].end(), v ^ x) - lower_bound(S[j + 1].begin(), S[j + 1].end(), v ^ x);
			}
			if(k > 0) {
				cnt += upper_bound(S[0].begin(), S[0].end(), x) - lower_bound(S[0].begin(), S[0].end(), x);
				v ^= val[k - 1];
				if(v == x) ++cnt;
			}
			for(int j = k * sz; j <= i; ++j) {
				v ^= a[j];	 
				if(v == x) ++cnt;
			}
			cout << cnt << '\n';
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
