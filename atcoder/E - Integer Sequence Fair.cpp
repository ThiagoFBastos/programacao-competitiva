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

i64 exp(i64 n, i64 p, int mod) {
	i64 ans = 1;
	n %= mod;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void solve() {
	i64 n, k, m;
	cin >> n >> k >> m;
	if(m % mod == 0) {
		cout << "0\n";
		return;
	}
	cout << exp(m, exp(k, n, mod - 1), mod) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}
