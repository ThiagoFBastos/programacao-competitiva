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

const double eps = 1e-9;

void solve() {
	int d, v0, v1, v2, flag = 0;
	double T = 0, t, x2 = 0;
	cin >> d >> v0 >> v1 >> v2 >> t;
	t = min(t, d / (double)v0);
	cout.precision(12);
	cout.setf(ios_base :: fixed);

	while(fabs(t - T) > eps) {
		if(flag == 0) {
			double x1 = min(1 + v1 * T, d + 0.0);
			double tt = min((d - x2) / v2, abs(x1 - x2) / (v2 - v1));
			x2 += min(tt, t - T) * v2;	
			T += min(tt, t - T);
			
		} else {
			double x0 = min(v0 * T, d + 0.0);
			double tt = abs(x0 - x2) / (v2 + v0);
			x2 -= min(tt, t - T) * v2;
			T += min(tt, t - T);
		}
		flag ^= 1;
	}
	cout << x2 << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

