#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, m;
	i64 ans = 0;

	cin >> n >> m;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		ans += (a + m - 1) / m * m - a;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
