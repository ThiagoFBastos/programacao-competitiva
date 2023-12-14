#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		if(k < (int)ceil(sqrt(n))) cout << "IMPOSSIBLE\n";
		else {
			vector<int> p;
			for(int i = k; i <= n; i += k) for(int j = 0; j < k; ++j) p.push_back(i - j);
			for(int i = n; int(p.size()) < n; --i) p.push_back(i);
			for(int& x : p) cout << x << ' ';
			cout << '\n';
		}
	}
	return 0;
}
