#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int tc = 1;

ld circle_area(int r) {
	return acos(-1.0L) * r * r;
}

void solve() {
	int r, a, b;
	ld area = 0;

	cin >> r >> a >> b;

	for(int t = 0; r; t ^= 1) {
		area += circle_area(r);
		if(t == 0) r *= a;
		else r /= b;
	}

	cout << "Case #" << tc++ << ": " << fixed << setprecision(12) << area << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}