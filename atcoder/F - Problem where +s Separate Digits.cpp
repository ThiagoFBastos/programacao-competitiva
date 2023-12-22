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
	string s;
	cin >> s;
	
	tuple<i64, i64, i64> dp = {s[0] - '0', 0, 1};
	
	for(int i = 1; i < (int)s.size(); ++i) {
		auto&[X, Y, Z] = dp;
		i64 x, y, z;
		x = (10 * X + 2 * Z * (s[i] - '0')) % mod;
		y = (Y * 2 + X) % mod;
		z = 2 * Z % mod;
		X = x, Y = y, Z = z;
	}
	
	auto [X, Y, Z] = dp;
	
	cout << (X + Y) % mod << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

