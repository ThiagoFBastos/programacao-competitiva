#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;
	map<i64, int> frq {{0,1}};
	i64 sum = 0, ans = 0;

	cin >> n;

	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		if(i % 2) sum -= a;
		else sum += a;
		ans += frq[sum]++;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
