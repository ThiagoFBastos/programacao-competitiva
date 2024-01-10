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
	
	i64 x, y = LLONG_MAX;
	
	cin >> x;

	for(int d = 1; d <= 9; ++d) {
		for(int r = -9; r <= 9; ++r) {
			i64 k = d;
			int f = d;
			while(k < x) {
				f += r;
				if(f < 0 || f > 9) break;
				k = 10 * k + f;
			}
			if(k >= x) y = min(y, k);
		}
	}

	cout << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
