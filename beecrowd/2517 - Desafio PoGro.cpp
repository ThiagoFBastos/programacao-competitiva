#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

double f(double x, int a, int b, int c) {
	return -x*x/a-x/b+c;
}

void solve() {
	int a, b, c;
	int xc, yc, xf;

	while(cin >> a >> b >> c >> xc >> yc >> xf) {
		double l = 0, r = xf;

		while(fabs(r - l) > EPS) {
			double lo = (2 * l + r) / 3;
			double hi = (2 * r + l) / 3;

			double d1 = hypot(xc - lo, yc - f(lo, a, b, c));
			double d2 = hypot(xc - hi, yc - f(hi, a, b, c));

			if(d1 < d2) r = hi;
			else l = lo;
		}

		cout << fixed << setprecision(2) << hypot(xc - r, yc - f(r, a, b, c)) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}