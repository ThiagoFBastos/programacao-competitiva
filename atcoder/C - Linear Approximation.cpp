#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;

	cin >> n;

	vector<int> a(n), b(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		b[i] = a[i] - i - 1;
	}
	
	sort(b.begin(), b.end());
	
	i64 x = n & 1 ? b[n/2] : (b[n/2]+b[n/2-1]) / 2, ans = 0;

	for(int i = 0; i < n; ++i) ans += abs(a[i] - x - i - 1ll);

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
 
