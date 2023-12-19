#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, even = 0;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			if(~x & 1) ++even;
		}
		if(even == n) cout << "second\n";
		else cout << "first\n";
	}
	return 0;
}
