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
	
	i64 n;
	int cnt = 1;

	cin >> n;

	for(i64 k = 1; k * k <= n - 1; ++k) {
		if((n - 1) % k) continue;
		cnt += k > 1;
		if(k * k != n - 1) ++cnt;
	}

	for(i64 k = 2; k * k <= n; ++k) {
		if(n % k) continue;
		i64 x = n;
		while(x % k == 0) x /= k;
		if(x % k == 1) ++cnt;
		if(k * k != n) {
			x = n;
			i64 j = n / k;
			while(x % j == 0) x /= j;
			cnt += x % j == 1;
		}
	}

	cout << cnt << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
