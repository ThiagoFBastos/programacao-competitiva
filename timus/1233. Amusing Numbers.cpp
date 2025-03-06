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

i64 count(i64 n, i64 m) {
	i64 cnt = 0;
	while(m > 0) {
		int d = m % 10;
		++cnt;
		m /= 10;
		for(int i = !m; i < d; ++i) {
			i64 x = 10 * m + i;
			for(i64 k = 1; k <= n / x; k *= 10)
				cnt += min(n, k * x + k - 1) - k * x + 1;
		}
	}
	return cnt;
}

void solve() {
	
	int n, k;

	cin >> n >> k;

	i64 lo = n, hi = 1e18;

	while(lo < hi) {
		i64 mid = (lo + hi) / 2;
		if(count(mid, n) >= k) hi = mid;
		else lo = mid + 1;
	}

	if(count(hi, n) != k) {
		cout << "0\n";
		return;
	}

	cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}