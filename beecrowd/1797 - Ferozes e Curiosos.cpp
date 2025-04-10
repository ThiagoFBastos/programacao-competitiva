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

struct point {
	double x, y;

	point() {x = y = 0;}
	point(double _x, double _y) : x {_x}, y {_y} {}

	double norm() {
		return hypot(x, y);
	}

	double norm2() {
		return x * x + y * y;
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

	bool operator<(point other) {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y < other.y;		
	}

	bool operator>(point other) {
		if(fabs(x - other.x) > EPS)
			return x > other.x;
		return y > other.y;		
	}

	bool operator<=(point other) {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y <= other.y;		
	}
	
	bool operator>=(point other) {
		if(fabs(x - other.x) > EPS)
			return x < other.x;
		return y >= other.y;		
	}
	
	bool operator==(point other) {
		return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
	}

	bool operator!=(point other) {
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

	point operator*(double k) {
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

bool intersects(point a[], point b[]) {
	if(a[2].x < b[0].x) return false;
	if(b[2].x < a[0].x) return false;
	if(a[2].y < b[0].y) return false;
	if(b[2].y < a[0].y) return false;
	return true;
}

bool canReach(point s1[], point s2[], double aah) {
	bool flag = false;
	if(intersects(s1, s2)) return true;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			point a = s1[i], b = s1[(i+1)&3], A = s2[j], B = s2[(j+1)&3]; 
			flag = flag || (closestToLineSegment(a, A, B) - a).norm2() <= aah;
			flag = flag || (closestToLineSegment(b, A, B) - b).norm2() <= aah;
			flag = flag || (closestToLineSegment(A, a, b) - A).norm2() <= aah;
			flag = flag || (closestToLineSegment(B, a, b) - B).norm2() <= aah;
		}
	}
	return flag;
}

const int N = 1e6 + 10;

ii delta[] = {
	{-1, -1},
	{-1, 1},
	{1, 1},
	{1, -1}
};

point s[N][4];

void solve() {
	int n;
	double aah;

	cin >> n >> aah;

	aah *= aah;

	for(int i = 0; i < n; ++i) {
		int x, y, l, k = 0;
		cin >> x >> y >> l;
		for(auto [dx, dy] : delta)
			s[i][k++] = {x + dx * l * 0.5, y + dy * l * 0.5};
	}

	bool can = true;
	for(int i = 0; i < n - 1; ++i) can = can && canReach(s[i], s[i + 1], aah);
	cout << (can ? "YEAH\n" : "OUCH\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}