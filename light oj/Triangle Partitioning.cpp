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

int caso;

void solve() {
	double AB, AC, BC, DE, r;
	cin >> AB >> AC >> BC >> r;
	double R = r / (1.0 + r);
	cout << "Case " << ++caso << ": " << fixed << setprecision(9) << sqrt(R) * AB << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}