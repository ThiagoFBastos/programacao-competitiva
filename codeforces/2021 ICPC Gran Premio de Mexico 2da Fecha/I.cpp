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

int g(int x) {
	int ans = 1;
	while(x > 0) {
		ans *= x % 10;
		x /= 10;
	}
	return ans;
}

int f(int x) {
	if(x <= 9) return 0;
	return 1 + f(g(x));
}

void solve() {
	int n;
	cin >> n;
	cout << f(n) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

