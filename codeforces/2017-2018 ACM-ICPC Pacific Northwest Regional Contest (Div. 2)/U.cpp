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
	array<double, 7> p;
	double ans = INT_MAX;
	
	for(int i = 1; i <= 6; ++i) cin >> p[i];

	for(int i = 1; i <= 6; ++i) {
		double e = 0;
		for(int j = 1; j <= 6; ++j) {
			if(i == j) continue;
			e += p[j] * j;
		}
		ans = min(ans, abs(i - (3.5 - e) / p[i]));
	}

	cout << fixed << setprecision(3) << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
