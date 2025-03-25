#include "bits/stdc++.h"
using namespace std;
void reverse(vector<int>& p, int L, int R) {
	for(; L < R; ++L, --R) swap(p[L], p[R]);
}
void solve() {
	int n, ans = 0;
	cin >> n;
	vector<int> p(n);
	for(int i = 0; i < n; ++i) cin >> p[i];
	for(int i = 0; i < n - 1; ++i) {
		int j = -1;
		for(int k = i; k < n; ++k) {
			if(p[k] == i + 1) {
				j = k;
				break;
			}
		}
		ans += j - i + 1;
		reverse(p, i, j);
	}
	cout << ans << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}