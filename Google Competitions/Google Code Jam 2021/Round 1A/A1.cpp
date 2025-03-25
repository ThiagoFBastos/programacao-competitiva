#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, ans = 0;
	cin >> n;
	vector<long long> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 1; i < n; ++i) {
		int k = 0;
		while(10 * a[i] <= a[i - 1]) {
			a[i] *= 10;
			k = 1;
			++ans;
		}
		if(a[i] <= a[i - 1]) {
			if(k) {
				if(a[i] + 9 > a[i - 1]) {
					while(a[i] <= a[i - 1]) ++a[i];
				} else {
					++ans;
					a[i] *= 10;
				}
			} else {
				a[i] *= 10;
				++ans;
			}
		}
		
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