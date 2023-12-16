#include "bits/stdc++.h"
 
using namespace std;
 
using pt = pair<int, int>;
using ll = long long;
#define X first
#define Y second
 
ll cross(pt a, pt b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X; 
}
 
int side(pt a, pt b, pt c) {
	b.X -= a.X, b.Y -= a.Y;
	c.X -= a.X, c.Y -= a.Y;
	ll val = cross(c, b);
	if(val > 0) return 1;
	else if(val < 0) return -1;
	return 0;
}
 
void solve() {
	pt p1, p2, p3;
	cin >> p1.X >> p1.Y >> p2.X >> p2.Y >> p3.X >> p3.Y;
	switch(side(p1, p2, p3)) {
		case 0:
			cout << "TOUCH\n";
			break;
		case 1:
			cout << "RIGHT\n";
			break;
		case -1:
			cout << "LEFT\n";
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
