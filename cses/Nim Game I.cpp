#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, r = 0;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			r ^= x;
		}
		if(r) cout << "first\n";
		else cout << "second\n";
	}
	return 0;
}
