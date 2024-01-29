#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	i64 a, b, x, y;

	cin >> a >> b >> x >> y;

	i64 g = gcd(x, y);

	x /= g;
	y /= g;

	cout << min(a / x, b / y) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

