#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;

	cin >> n;

	cout << "6 10 15 ";

	int l = 16;

	for(int i = 3; i < n; ++i) {
		while(l % 6 && l % 10 && l % 15) ++l;
		cout << l++ << ' ';
	}

	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
