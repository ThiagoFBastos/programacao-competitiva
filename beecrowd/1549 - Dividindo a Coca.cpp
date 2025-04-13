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

double volumeCone(double r, double h) {
	return r * r * acos(-1) * h / 3;
}

double volumeCilindro(double r, double h) {
	return r * r * acos(-1) * h;
}

void solve() {
	int N, L, b, B, H;

	cin >> N >> L;
	cin >> b >> B >> H;

	cout.precision(2);
	cout.setf(ios_base :: fixed);

	double l = 0, r = H;
	
	if(b == B) {
		while(fabs(l - r) > EPS) {
			double m = (l + r) / 2;
			if(volumeCilindro(B, m) * N >= L) r = m;
			else l = m;
		}
	} else {
		double h = H * b / double(B - b);
		l += h, r += h;
		while(fabs(l - r) > EPS) {
			double m = (l + r) / 2;
			double _b = m * B / (h + H);
			double V = volumeCone(_b, m) - volumeCone(b, h);
			if(V * N >= L) r = m;
			else l = m;
		}
		r -= h;
	}

	cout << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}