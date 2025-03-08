#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

#define eps 1e-9
#define x first
#define y second
#define vx real()
#define vy imag()

using vec = complex<double>;
using point = pair<double, double>;

vec dir(point& p1, point& p2) {
	return {p1.x - p2.x, p1.y - p2.y};
}

int sign(double n) {
	return n < -eps ? -1 : (n > eps ? 1 : 0);
}

int side(vec v, point src, point p) {
	return sign((conj(v) * dir(src, p)).vx);
}

double getX(vec& u, point& src, double y) {
	if(sign(u.vy) == 0) return -1;
	double k = (y - src.y) / u.vy;
	return src.x + u.vx * k;
}

double getY(vec& u, point& src, double x) {
	if(sign(u.vx) == 0) return -1;
	double k = (x - src.x) / u.vx;
	return src.y + u.vy * k;
}

bool atRange(double a, double b, double c) {
	return sign(c - a) >= 0 && sign(b - c) >= 0;
}

double triangle_area(point a, point b, point c) {
	return 0.5 * abs(a.x * (b.y - c.y) - a.y * (b.x - c.x) + b.x * c.y - b.y * c.x);	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int L, A;
	point p1, p2;
	cin >> L >> A >> p1.x >> p1.y >> p2.x >> p2.y;
	cout.precision(6);
	cout.setf(ios_base :: fixed);
	if(p1.x == p2.x && p2.y == p1.y) 
		cout << 0.0 << ' ' << 0.0 << '\n';
	else {
		vec ortho {-p2.y + p1.y, p2.x - p1.x};
		vec v = dir(p1, p2);
		point mid;

		mid.x = (p1.x + p2.x) / 2.0;
		mid.y = (p1.y + p2.y) / 2.0;

		double xa, xb, ya, yb;
		int s = side(v, mid, p1);
		vector<point> p, r;

		if(s == side(v, mid, {0, 0})) p.push_back({0, 0});
		if(s == side(v, mid, {L, 0})) p.push_back({L, 0});
		if(s == side(v, mid, {0, A})) p.push_back({0, A});
		if(s == side(v, mid, {L, A})) p.push_back({L, A});

		xa = getX(ortho, mid, A);
		xb = getX(ortho, mid, 0);
		ya = getY(ortho, mid, L);
		yb = getY(ortho, mid, 0);
		
		if(atRange(0, L, xa)) r.push_back({xa, A});
		if(atRange(0, L, xb)) r.push_back({xb, 0});
		if(atRange(0, A, ya)) r.push_back({L, ya});
		if(atRange(0, A, yb)) r.push_back({0, yb});
			
		double a = L * A, at;

		if(p.size() == 1)
			at = triangle_area(r[0], r[1], p[0]);
		else {
			if(sign(p[0].x - r[0].x) && sign(p[0].y - r[0].y))
				at = triangle_area(p[0], p[1], r[0]) + triangle_area(p[0], r[0], r[1]);
			else
				at = triangle_area(p[0], p[1], r[1]) + triangle_area(p[0], r[0], r[1]);
		}

		cout << at / a << ' ' << (a - at) / a << '\n';
	}
	return 0;
}