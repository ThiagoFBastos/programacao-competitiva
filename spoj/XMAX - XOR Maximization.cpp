#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n;

	cin >> n;

	vector<i64> a(n);

	for(i64& v : a) cin >> v;

	for(int i = 60, j = 0; i >= 0; --i) {
		for(int k = j; k < n; ++k) {
			if(a[k] & (1ll << i)) {
				swap(a[k], a[j]);
				break;
			}
		}
		if(~a[j] & (1ll << i)) continue;
		for(int k = ++j; k < n; ++k) {
			if(a[k] & (1ll << i))
				a[k] ^= a[j - 1];
		}
	}

	i64 ans = 0;

	for(int i = 0; i < n; ++i) {
		if((a[i] ^ ans) > ans) 
			ans ^= a[i];
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
