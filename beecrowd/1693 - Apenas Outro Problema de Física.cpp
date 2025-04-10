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

double amplitude(double d, int r, int h, int v, int g) {
	double b = v * sin(d);
	return v * cos(d) * (b + sqrt(b * b + 2 * h * g)) / g;
}

void solve() {

	int r, h, v, g;

	while(cin >> r >> h >> v >> g) {
		double lo = 0, hi = acos(0);

		while(fabs(hi - lo) > EPS) {
			double L = (2 * lo + hi) / 3;
			double R = (2 * hi + lo) / 3;
			if(amplitude(L, r, h, v, g) < amplitude(R, r, h, v, g)) lo = L;
			else hi = R;
		}

		double dist = amplitude(hi, r, h, v, g);

		cout << (dist > r ? "Y\n" : "N\n");
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