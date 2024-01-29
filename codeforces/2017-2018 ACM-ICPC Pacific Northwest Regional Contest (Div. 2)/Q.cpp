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

i64 sum(int a, int b) {
	return (b - a + 1ll) * (a + b) / 2;
}

void solve() {
	int n;

	cin >> n;
	
	int lo = 1, hi = n;
	i64 t = n * (n - 1ll) / 2;

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(2 * sum(n - mid, n - 1) >= t) hi = mid;
		else lo = mid + 1;
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
