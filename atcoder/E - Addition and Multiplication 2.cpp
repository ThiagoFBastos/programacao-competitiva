#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, X = INT_MAX;

	cin >> n;
	vector<int> c(10);
	
	for(int i = 1; i <= 9; ++i) {
		cin >> c[i];
		X = min(X, c[i]);
	}

	for(int i = n; i >= 0; --i) {
		if((i64)X * i > n) continue;
		int hi = 9, m = 0, k = i;
		string y;
		while(hi > 0 && k > 0) {
			if(m + c[hi] + X * (k - 1ll) <= n) {	
				y += hi + '0';
				m += c[hi], --k;
			} else --hi;
		}
		cout << y << '\n';
		break;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
