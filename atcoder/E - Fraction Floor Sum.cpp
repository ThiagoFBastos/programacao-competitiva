#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	i64 n, ans = 0;

	cin >> n;

	for(i64 k = 1; k * k <= n; ++k) {
		i64 L = n / (k + 1) + 1, R = n / k;
		ans += k * (R - L + 1);
		if(k < L || k > R) ans += n / k;
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
