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

i64 sum(i64 a, i64 b) {
	return (a + b) * (b - a + 1ll) / 2;
}

void solve() {
	int n, m, z = 0;
	i64 P = 0, Q = 0, ans = LLONG_MIN;

	cin >> n >> m;

	vector<int> x(n), y(n);

	for(int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
		
		i64 S = z * Q + P;

		if(x[i]) {
			i64 b = 2 * Q + x[i];
			i64 z = -b / (2 * x[i]);
			for(i64 k = max(1ll, z - 5); k <= min<i64>(z + 5, y[i]); ++k) {
				i64 K = S + k * Q + k * (k + 1ll) / 2 * x[i];
				ans = max(ans, K);
			}
		}

		P -= sum(z, z + y[i] - 1) * x[i];
		Q += (i64)x[i] * y[i];
		z += y[i];

		ans = max(ans, z * Q + P);
	}	

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
