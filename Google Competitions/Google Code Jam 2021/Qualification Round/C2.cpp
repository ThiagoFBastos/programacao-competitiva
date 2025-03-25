#include "bits/stdc++.h"
using namespace std;
void reverse(vector<int>& p, int L, int R) {
	for(; L < R; ++L, --R) swap(p[L], p[R]);
}
void solve() {
	int n, c;
	cin >> n >> c;
	if(c > n * (n + 1) / 2 - 1 || c < n - 1) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	vector<int> p(n);
	int L = 0, R = n - 1;
	for(int i = 0; i < n; ++i) p[i] = i + 1;
	for(int i = 1; i < n; ++i) {
		if(c >= 2 * (n - i)) {
			if(i & 1) {
				for(int k = L + 1; k <= R; ++k) swap(p[k], p[k - 1]);
				--R;
			} else {
				for(int k = R - 1; k >= L; --k) swap(p[k], p[k + 1]);
				++L;
			}
			reverse(p, L, R);
			c -= n - i + 1;
		} else {
			c -= n - i - 1;
			if(i & 1) {
				for(int k = L + 1; k < L + c; ++k) swap(p[k], p[k - 1]);
				reverse(p, L, L + c - 2);
				--R;
			} else {
				for(int k = R - 1; k > R - c; --k) swap(p[k], p[k + 1]);
				reverse(p, R - c + 2, R);
				++L;
			}
			break;
		}
	}
	for(int x : p) cout << x << ' ';
	cout << '\n';
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