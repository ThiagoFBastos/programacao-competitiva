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
	int p, q;

	cin >> p >> q;

	if(p < 2ll * q) {
		cout << "0 0\n";
		return;
	}

	i64 X = 1ll * p * p - 4ll * q * q;

	int x = sqrt(X);

	if(1ll * x * x != X) {
		cout << "0 0\n";
		return;
	}

	int a = p + x;
	int b = 2 * q;
	int g = gcd(a, b);

	cout << a / g << ' ' << b / g << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

