#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, ans = 0;
	cin >> n;
	vector<string> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 1; i < n; ++i) {
		if(size(a[i]) < size(a[i - 1])) {
			int k = size(a[i]), m;
			m = k;
			while(size(a[i]) < size(a[i - 1])) {
				a[i] += "0";
				++ans;
			}
			if(a[i] <= a[i - 1]) {
				for(int j = m; j < size(a[i]); ++j) a[i][j] = a[i - 1][j];
				for(int j = size(a[i]) - 1; j >= m; --j) {
					if(a[i - 1][j] < '9') {
						a[i][j] = a[i - 1][j] + 1;
						for(++j; j < size(a[i]); ++j) a[i][j] = '0';					
						break;
					}
				}
				if(a[i] <= a[i - 1]) {
					for(int j = m; j < size(a[i]); ++j) a[i][j] = '0';
					a[i] += "0";
					++ans;
				}
			}
		} else if(size(a[i]) == size(a[i - 1]) && a[i] <= a[i - 1]) {
			a[i] += "0";
			++ans;
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