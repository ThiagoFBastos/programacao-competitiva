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

const int mod = 998244353;

void solve() {
	
	int h, w, k;
	int x1, y1, x2, y2;

	cin >> h >> w >> k;
	cin >> x1 >> y1 >> x2 >> y2;

	int col = 0, row = 0, other = 0, dest = 0;

	col = y1 == y2 && x1 != x2;
	row = x1 == x2 && y1 != y2;
	other = x1 != x2 && y1 != y2;
	dest = x1 == x2 && y1 == y2;

	for(int i = 1; i <= k; ++i) {
		int c = col;
		int r = row;
		int o = other;
		int d = dest;

		dest = (c + r) % mod;
		col = (c * (h - 2ll) + d * (h - 1ll) + o) % mod; 
		row = (r * (w - 2ll) + d * (w - 1ll) + o) % mod;
		other = (o * (h + w - 4ll) + c * (w - 1ll) + r * (h - 1ll)) % mod;
	}

	cout << (dest + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
