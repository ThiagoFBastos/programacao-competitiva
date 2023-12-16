#include "bits/stdc++.h"
 
using namespace std;
 
#define X first
#define Y second
 
using pt = pair<int, int>;
using seg = tuple<int, int, int, int>;
using ll = long long;
 
int sig(ll x) {
	if(x < 0) return -1;
	return x > 0 ? 1 : 0;
}
 
bool is_percent(ll a, ll b) {
	if(!b && a || a && sig(a) != sig(b)) return false;
	return abs(a) <= abs(b);
}
 
int on_line(pt a, pt b, pt c) {
	ll dx = b.X - a.X, dy = b.Y - a.Y, x = c.X - a.X, y = c.Y - a.Y;
	return is_percent(x, dx) && is_percent(y, dy) && x * dy == y * dx;
}
 
bool intersect(seg a, seg b) {
	auto [ax0, ay0, ax1, ay1] = a;
	auto [bx0, by0, bx1, by1] = b;
	pt u = {ax0, ay0}, du = {ax1 - ax0, ay1 - ay0};
	pt v = {bx0, by0}, dv = {bx1 - bx0, by1 - by0};
	v.X -= u.X, v.Y -= u.Y;
	dv.X *= -1, dv.Y *= -1;
	ll det = 1ll * du.X * dv.Y - 1ll * du.Y * dv.X;
	ll detx = 1ll * v.X * dv.Y - 1ll * v.Y * dv.X;
	ll dety = 1ll * du.X * v.Y - 1ll * du.Y * v.X;
	if(det == 0) {
		int cnt = on_line({ax0, ay0}, {ax1, ay1}, {bx0, by0});
		cnt += on_line({ax0, ay0}, {ax1, ay1}, {bx1, by1});
		cnt += on_line({bx0, by0}, {bx1, by1}, {ax0, ay0});
		cnt += on_line({bx0, by0}, {bx1, by1}, {ax1, ay1});
		return cnt;
	}
	return is_percent(detx, det) && is_percent(dety, det);
}
 
void solve() {
	int x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	cout << (intersect({x1, y1, x2, y2}, {x3, y3, x4, y4}) ? "YES\n" : "NO\n");
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
