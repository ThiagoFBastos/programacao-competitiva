#include "bits/stdc++.h"
using namespace std;
int n, q;
void solve() {
	vector<int> a(2);
	a[0] = 1;
	a[1] = 2;
	for(int i = 3; i <= n; ++i) {
		int L = 0, R = i - 2;
		while(true) {
			int ans;
			if(R - L == 1) {
				cout << a[L] << ' ' << a[R] << ' ' << i << '\n';
				cout.flush();
				cin >> ans;
				if(ans == i) a.insert(a.begin() + R, i);
				else if(ans == a[L]) a.insert(a.begin() + L, i);
				else a.insert(a.begin() + R + 1, i);
				break;
			} else if(R - L == 2) {
				cout << a[L] << ' ' << a[R] << ' ' << i << '\n';
				cout.flush();
				cin >> ans;		
				if(ans == i) {
					cout << a[L] << ' ' << a[L + 1] << ' ' << i << '\n';
					cout.flush();
					cin >> ans;
					if(ans == i) a.insert(a.begin() + L + 1, i);
					else a.insert(a.begin() + R, i);
				}
				else if(ans == a[L]) a.insert(a.begin() + L, i);
				else a.insert(a.begin() + R + 1, i);
				break;
			} else {
				int l, r;
				l = L + (R - L) / 3;
				r = R - (R - L) / 3;
				cout << a[l] << ' ' << a[r] << ' ' << i << '\n';
				cout.flush();
				cin >> ans;
				if(ans == i) {
					if(l + 1 < r - 1) L = l + 1, R = r - 1;
					else L = l, R = r;
				} else if(ans == a[l]) R = l - 1 > L ? l - 1 : l;
				else L = r + 1 < R ? r + 1 : r;
			}
		}
	}
	for(int x : a) cout << x << ' ';
	cout << '\n';
	cout.flush();
	int ans;
	cin >> ans;
	if(ans == -1) exit(0);
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t >> n >> q;
	for(int i = 1; i <= t; ++i) solve();
	return 0;
}