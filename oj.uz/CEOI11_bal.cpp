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
using i128 = __int128;
	
struct point {
	ld x, y;
};
 
ld minRadius(point A, ld x0) {
	ld l = 0, r = 1e9;
	while(fabs(l - r) > EPS) {
		ld m = (l + r) / 2;
		ld x = A.x - x0, y = A.y - m;
		if(x * x + y * y <= (A.y + m) * (A.y + m)) r = m;
		else l = m;
	}
	return r;
}
 
void solve() {
	int n;
	vector<point> c;
 
	cin >> n;
 
	vector<int> x(n), r(n);
 
	for(int i = 0; i < n; ++i) cin >> x[i] >> r[i];
	
	cout.precision(3);
	cout.setf(ios_base :: fixed);
 
	c.pb({0.0L + x[0], 0.0L + r[0]});
 
	cout << 0.0L + r[0] << '\n';
 
	for(int i = 1; i < n; ++i) {
		ld radius = r[i];
		while(!c.empty()) {
			radius = min(radius, minRadius(c.back(), x[i]));
			if(radius <= c.back().y) break;
			c.pop_back();
		}
		c.pb({0.0L + x[i], 0.0L + radius});
		cout << radius << '\n';
	}
}		
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
