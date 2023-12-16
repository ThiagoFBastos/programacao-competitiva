#include "bits/stdc++.h"
 
using namespace std;
 
#define X first
#define Y second
 
using pt = pair<int, int>;
using ll = long long;
 
int mod_sum(int x, int n) {
	return x >= n ? x - n : x;
}
 
ll cross(pt a, pt b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X;
}
 
int above(pt a, pt b) {
	return a.X >= b.X;
}
 
ll det(pt a, pt b, pt c) {
	return 1ll * b.X * c.Y - 1ll * b.Y * c.X
		  -1ll * a.X * (c.Y - b.Y)
		  +1ll * a.Y * (c.X - b.X);
}
 
bool inside(vector<pt>& pol, pt p) {
	int n = size(pol), cnt = 0;
	for(int i = 0; i < n; ++i) {
		int j = mod_sum(i + 1, n);
		cnt += (above(pol[j], p) - above(pol[i], p)) * det(p, pol[i], pol[j]) > 0;
	}
	return cnt & 1;
}
 
bool onLine(pt a, pt b, pt c) {
	if(a.Y > b.Y) swap(a, b);
	if(c.Y < a.Y || c.Y > b.Y) return false;
	if(a.Y == b.Y && b.Y == c.Y && (c.X < min(a.X, b.X) || c.X > max(a.X, b.X))) return false;
	c.X -= a.X, c.Y -= a.Y, b.X -= a.X, b.Y -= a.Y;
	return cross(c, b) == 0;
}
 
bool boundary(vector<pt>& pol, pt p) {
	bool ok = false;
	int n = size(pol);
	for(int i = 0; i < n; ++i) ok = ok || onLine(pol[i], pol[mod_sum(i + 1, n)], p);
	return ok;
}
 
void solve() {
	int n, m;
	cin >> n >> m;
	vector<pt> pol(n);
	for(auto& [x, y] : pol) cin >> x >> y;
	while(m--) {
		int x, y;
		cin >> x >> y;
		if(boundary(pol, {x, y})) cout << "BOUNDARY\n";
		else if(inside(pol, {x, y})) cout << "INSIDE\n";
		else cout << "OUTSIDE\n";
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
