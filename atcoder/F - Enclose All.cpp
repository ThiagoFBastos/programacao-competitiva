#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
	double x, y;

	point() {x = y = 0;}
	point(double _x, double _y) : x {_x}, y {_y} {}

	double norm() {
		return hypot(x, y);
	}

	point normalized() {
		return point(x, y) * (1.0 / norm());
	}

	double angle() {
		return atan2(y, x);
	}

	double polarAngle() {
		double a = atan2(y, x);
		return a < 0 ? a + 2 * acos(-1) : a;
	}

	bool operator<(point other) const {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y < other.y;		
	}

	bool operator>(point other) const {
		if(fabs(x - other.x) > EPS)
			return x > other.x;
		return y > other.y;		
	}

	bool operator<=(point other) const {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y <= other.y;		
	}
	
	bool operator>=(point other) const {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y >= other.y;		
	}
	
	bool operator==(point other) const {
		return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
	}

	bool operator!=(point other) const {
		return !(*this == other);
	}

	point operator+(point other) const {
		return {x + other.x, y + other.y};
	}

	point operator-(point other) const {
		return {x - other.x, y - other.y};
	}

	point& operator+=(point other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	
	point& operator-=(point other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	point& operator*=(double k) {
		x *= k;
		y *= k;		
		return *this;
	}

	point operator*(double k) const {
		return {x * k, y * k};
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double cross(point p1, point p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q - p, r - p) > 0;
}

bool cw(point p, point q, point r) {
	return cross(q - p, r - p) < 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p - q, r - p)) < EPS;
}

point rotate(point p, double rad) {
	return {p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad)};
}

double angle(point a, point o, point b) {
	return acos(inner(a - o, b - o) / dist(o, a) * dist(o, b));
}

point proj(point u, point v) {
	return v * (inner(u, v) / inner(v, v));
}

bool between(point p, point q, point r) {
	return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A - B, p - q);
	double a = cross(A, B);
	double b = cross(p, q);
	return (p - q) * (a / c) - (A - B) * (b / c);
}

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
}	

bool segIntersects(point a, point b, point p, point q) {
	if(parallel(a - b, p - q))
		return between(a, p, b) || between(a, q, b) || between(p, a, q) || between(p, b, q);

	point i = lineIntersectSeg(a, b, p, q);

	return between(a, i, b) && between(p, i, q);
}

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p - a, b - a) / inner(b - a, b - a);
	if(u < 0) return a;
	if(u > 1) return b;
	return a + (b - a) * u;
}

struct circle {
	point c;
	double r;

	circle() {
		c = point();
		r = 0;
	}

	circle(point _c, double _r) : c {_c}, r {_r} {}

	double area() {
		return acos(-1) * r * r;
	}

	double chord(double rad) {
		return 2 * r * sin(rad / 2);
	}

	double sector(double rad) {
		return 0.5 * rad * area() / acos(-1);
	}

	bool intersects(circle other) {
		return dist(c, other.c) < r + other.r;
	}

	bool contains(point p) {
		return dist(c, p) <= r + EPS;
	}

	pair<point, point> getTangentPoint(point p) {
		double d1 = dist(p, c);
		double theta = asin(r / d1);
		point p1 = rotate(c - p, -theta);
		point p2 = rotate(c - p, theta);
		p1 = p1 * (sqrt(d1 * d1 - r * r) / d1) + p;
		p2 = p2 * (sqrt(d1 * d1 - r * r) / d1) + p;	
		return {p1, p2};
	}

	vector<pair<point, point>> getTangentSegs(circle other) {
		vector<pair<point, point>> ans;
		
		double d = dist(other.c, c);

		double dr = abs(r - other.r), sr = r + other.r;

		if(dr >= d) return ans;

		double u = acos(dr / d);

		point dc1 = (other.c - c).normalized() * r;
		point dc2 = (other.c - c).normalized() * other.r;

		ans.pb({c + rotate(dc1, u), other.c + rotate(dc2, u)});
		ans.pb({c + rotate(dc1, -u), other.c + rotate(dc2, -u)});

		if(sr >= d) return ans;

		double v = acos(sr / d);

		dc2 = (c - other.c).normalized() * other.r;

		ans.pb({c + rotate(dc1, v), other.c + rotate(dc2, v)});
		ans.pb({c + rotate(dc1, -v), other.c + rotate(dc2, -v)});

		return ans;
	}

	pair<point, point> getIntersectionPoints(circle other) {
		assert(intersects(other));
		
		double d = dist(c, other.c);

		double u = acos((r * r + d * d - other.r * other.r) / (2 * r * d));

		point dc = (other.c - c).normalized() * r;

		return {c + rotate(dc, u), c + rotate(dc, -u)};	
	}
};

circle circumcircle(point a, point b, point c) {
	point u = {(b - a).y, -(b - a).x};
	point v = {(c - a).y, -(c - a).x};
	point n = (c - b) * 0.5;
	circle ans;
	double t = cross(u, n) / cross(v, u);
	ans.c = (a + c) * 0.5 + v * t;
	ans.r = dist(ans.c, a);
	return ans; 
}

int insideCircle(point p, circle c) {
	if(fabs(dist(p, c.c) - c.r) < EPS) return 1;
	else if(dist(p, c.c) < c.r) return 0;
	return 2; // 0 = inside /1 = border /2 = outside
}	

circle incircle(point p1, point p2, point p3) {
	double m1 = dist(p2, p3);
	double m2 = dist(p1, p3);
	double m3 = dist(p1, p2);
	point c = (p1 * m1 + p2 * m2 + p3 * m3) * (1.0 / (m1 + m2 + m3));
	double s = 0.5 * (m1 + m2 + m3);
	double r = sqrt(s * (s - m1) * (s - m2) * (s - m3)) / s;
	return {c, r};
}

circle minimumCircle(vector<point>& p) {
	random_shuffle(all(p));
	int n = p.size();
	circle C(p[0], 0.0);
	for(int i = 0; i < n; ++i) {
		if(C.contains(p[i])) continue;
		C = circle(p[i], 0.0);
		for(int j = 0; j < i; ++j) {
			if(C.contains(p[j])) continue;
			C = circle((p[j] + p[i]) * 0.5, 0.5 * dist(p[j], p[i]));
			for(int k = 0; k < j; ++k) {
				if(C.contains(p[k])) continue;
				C = circumcircle(p[j], p[i], p[k]);
			}
		}
	}
	return C;
}

void solve() {
	int n;
	cin >> n;
	vector<point> p(n);
	vector<circle> c(n);
	for(auto& [x, y] : p) cin >> x >> y;
	double lo = 0, hi = 1e5;
	auto contains = [&](circle c) {
		for(auto& q : p) if(!c.contains(q)) return false;
		return true;
	};
	while(fabs(lo - hi) > EPS) {
		double m = (lo + hi) / 2;
		bool found = false;
		for(int i = 0; i < n; ++i) c[i] = {p[i], m};
		for(int i = 0; i < n && !found; ++i) {
			found = found || contains(c[i]);
			for(int j = i + 1; j < n && !found; ++j) {
				if(!c[i].intersects(c[j])) continue;
				auto [p1, p2] = c[i].getIntersectionPoints(c[j]);
				found = found || contains({p1, m}) || contains({p2, m});
			}
		}
		if(found) hi = m;
		else lo = m;
	}
	cout << fixed << setprecision(9) << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
