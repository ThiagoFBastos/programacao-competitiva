#include "bits/stdc++.h"
using namespace std;
int largest_subarray(vector<int>& a) {
	int n = size(a), r = INT_MAX, ans = 0;
	vector<int> cnt(n + 1, 0);
	for(int k = n - 1; k; --k) {
		if(a[k] - a[k - 1] == r) cnt[k] = 1 + cnt[k + 1];
		else cnt[k] = 1;
		ans = max(ans, 1 + cnt[k]);
		r = a[k] - a[k - 1];
	}
	r = INT_MAX;
	int L = 0;
	for(int k = 1; k < n - 1; ++k) {
		int x = a[k] - a[k - 1];
		if(r == x) ++L;
		else L = 1;
		r = x;
		if(a[k + 1] - a[k] != x) {
			int v = a[k + 1], t = L + 1;
			a[k + 1] = a[k] + x;
			if(k + 2 < n && a[k + 2] - a[k + 1] == x) {
				++t;
				if(k + 3 < n && a[k + 3] - a[k + 2] == x) t += cnt[k + 3];
			}
			a[k + 1] = v;
			ans = max(ans, 1 + t);
		}
	}
	return ans;
}
void solve() {
	int n, ans;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	if(n <= 2) {
		cout << n << '\n';
		return;
	}
	ans = max(2, largest_subarray(a));
	reverse(a.begin(), a.end());
	ans = max(ans, largest_subarray(a));
	for(int k = 0; k < n - 2; ++k) {
		if((a[k] + a[k + 2]) % 2 == 0) 
			ans = max(ans, 3);
	}
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
	return 0;
}