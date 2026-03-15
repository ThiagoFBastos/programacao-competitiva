#include <bits/stdc++.h>

using namespace std;

constexpr double EPS = 1e-9;

struct point {
	double x, y;

	point() : x(), y() {}
	point(double _x, double _y) : x {_x}, y {_y} {}

	double norm() const {
		return std::hypot(x, y);
	}

	point normalized() const {
		return point(x, y) * (1.0 / norm());
	}

	double angle() const {
		return std::atan2(y, x);
	}

	double polarAngle() const {
		double a = std::atan2(y, x);
		return a < 0 ? a + 2 * std::acos(-1) : a;
	}

	bool operator<(const point& other) const {
		if(std::fabs(x - other.x) > EPS)
			return x < other.x;
		return y < other.y;		
	}

	bool operator>(const point& other) const {
		if(std::fabs(x - other.x) > EPS)
			return x > other.x;
		return y > other.y;		
	}

	bool operator<=(const point& other) const {
		if(std::fabs(x - other.x) > EPS)
			return x < other.x;
		return y <= other.y;		
	}
	
	bool operator>=(const point& other) const {
		if(std::fabs(x - other.x) > EPS)
			return x < other.x;
		return y >= other.y;		
	}
	
	bool operator==(const point& other) const {
		return std::fabs(x - other.x) < EPS && std::fabs(y - other.y) < EPS;
	}

	bool operator!=(const point& other) const {
		return !(*this == other);
	}

	point operator+(const point& other) const {
		return {x + other.x, y + other.y};
	}

	point operator-(const point& other) const {
		return {x - other.x, y - other.y};
	}

	point& operator+=(const point& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	
	point& operator-=(const point& other) {
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

namespace point_utils
{
inline double dist(const point& p1, const point& p2) {
	return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

inline double inner(const point& p1, const point& p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

inline double cross(const point& p1, const point& p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

inline bool ccw(const point& p, const point& q, const point& r) {
	return cross(q - p, r - p) > EPS;
}

inline bool cw(const point& p, const point& q, const point& r) {
	return cross(q - p, r - p) < -EPS;
}

inline bool collinear(const point& p, const point& q, const point& r) {
	return std::fabs(cross(p - q, r - p)) < EPS;
}

inline point rotate(const point& p, double rad) {
	return {p.x * std::cos(rad) - p.y * std::sin(rad), p.x * std::sin(rad) + p.y * std::cos(rad)};
}

inline double angle(const point& a, const point& o, const point& b) {
	return std::acos(inner(a - o, b - o) / dist(o, a) * dist(o, b));
}

inline point proj(const point& u, const point& v) {
	return v * (inner(u, v) / inner(v, v));
}

inline bool between(const point& p, const point& q, const point& r) {
	return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

inline point lineIntersectSeg(const point& p, const point& q, const point& A, const point& B) {
	double c = cross(A - B, p - q);
	double a = cross(A, B);
	double b = cross(p, q);
	return (p - q) * (a / c) - (A - B) * (b / c);
}

inline bool parallel(const point& a, const point& b) {
	return std::fabs(cross(a, b)) < EPS;
}	

inline bool segIntersects(const point& a, const point& b, const point& p, const point& q) {
	if(parallel(a - b, p - q))
		return between(a, p, b) || between(a, q, b) || between(p, a, q) || between(p, b, q);

	auto i = lineIntersectSeg(a, b, p, q);

	return between(a, i, b) && between(p, i, q);
}

inline point closestToLineSegment(const point& p, const point& a, const point& b) {
	double u = inner(p - a, b - a) / inner(b - a, b - a);
	if(u < 0) return a;
	if(u > 1) return b;
	return a + (b - a) * u;
}

}

struct circle 
{
	point c;
	double r;

	circle(): c(), r() {}

	circle(point _c, double _r) : c {_c}, r {_r} {}

	double area() const 
	{
		return std::acos(-1) * r * r;
	}

	double chord(double rad) const 
	{
		return 2 * r * std::sin(rad / 2);
	}

	double sector(double rad) const 
	{
		return 0.5 * rad * area() / std::acos(-1);
	}

	bool intersects(const circle& other) const 
	{
		return point_utils::dist(c, other.c) < r + other.r;
	}

	bool contains(const point& p) const 
	{
		return point_utils::dist(c, p) <= r + EPS;
	}

	std::pair<point, point> getTangentPoint(const point& p) const 
	{
		double d1 = point_utils::dist(p, c);
		double theta = std::asin(r / d1);
		auto p1 = point_utils::rotate(c - p, -theta);
		auto p2 = point_utils::rotate(c - p, theta);
		p1 = p1 * (std::sqrt(d1 * d1 - r * r) / d1) + p;
		p2 = p2 * (std::sqrt(d1 * d1 - r * r) / d1) + p;	
		return {p1, p2};
	}

	std::vector<std::pair<point, point>> getTangentSegs(const circle& other) const 
	{
		std::vector<std::pair<point, point>> ans;
		
		double d = point_utils::dist(other.c, c);

		double dr = std::abs(r - other.r), sr = r + other.r;

		if(dr >= d) return ans;

		double u = std::acos(dr / d);

		point dc1 = (other.c - c).normalized() * r;
		point dc2 = (other.c - c).normalized() * other.r;

		ans.push_back({c + point_utils::rotate(dc1, u), other.c + point_utils::rotate(dc2, u)});
		ans.push_back({c + point_utils::rotate(dc1, -u), other.c + point_utils::rotate(dc2, -u)});

		if(sr >= d) return ans;

		double v = acos(sr / d);

		dc2 = (c - other.c).normalized() * other.r;

		ans.push_back({c + point_utils::rotate(dc1, v), other.c + point_utils::rotate(dc2, v)});
		ans.push_back({c + point_utils::rotate(dc1, -v), other.c + point_utils::rotate(dc2, -v)});

		return ans;
	}

	std::pair<point, point> getIntersectionPoints(const circle& other) const
	{
		assert(intersects(other));
		
		double d = point_utils::dist(c, other.c);

		double u = std::acos((r * r + d * d - other.r * other.r) / (2 * r * d));

		auto dc = (other.c - c).normalized() * r;

		return {c + point_utils::rotate(dc, u), c + point_utils::rotate(dc, -u)};	
	}
};

namespace circle_utils {
	
circle circumcircle(const point& a, const point& b, const point& c) 
{
	point u = {(b - a).y, -(b - a).x};
	point v = {(c - a).y, -(c - a).x};
	auto n = (c - b) * 0.5;
	circle ans;
	double t = point_utils::cross(u, n) / point_utils::cross(v, u);
	ans.c = (a + c) * 0.5 + v * t;
	ans.r = point_utils::dist(ans.c, a);
	return ans; 
}

int insideCircle(const point& p, const circle& c) 
{
	if(std::fabs(point_utils::dist(p, c.c) - c.r) < EPS) return 1;
	else if(point_utils::dist(p, c.c) < c.r) return 0;
	return 2; // 0 = inside /1 = border /2 = outside
}	

circle incircle(const point& p1, const point& p2, const point& p3) 
{
	double m1 = point_utils::dist(p2, p3);
	double m2 = point_utils::dist(p1, p3);
	double m3 = point_utils::dist(p1, p2);
	auto c = (p1 * m1 + p2 * m2 + p3 * m3) * (1.0 / (m1 + m2 + m3));
	double s = 0.5 * (m1 + m2 + m3);
	double r = sqrt(s * (s - m1) * (s - m2) * (s - m3)) / s;
	return {c, r};
}

circle minimumCircle(std::vector<point>& p) 
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

	std::shuffle(p.begin(), p.end(), rng);
	int n = p.size();
	circle C(p[0], 0.0);
	for(int i = 0; i < n; ++i) {
		if(C.contains(p[i])) continue;
		C = circle(p[i], 0.0);
		for(int j = 0; j < i; ++j) {
			if(C.contains(p[j])) continue;
			C = circle((p[j] + p[i]) * 0.5, 0.5 * point_utils::dist(p[j], p[i]));
			for(int k = 0; k < j; ++k) {
				if(C.contains(p[k])) continue;
				C = circumcircle(p[j], p[i], p[k]);
			}
		}
	}
	return C;
}

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    constexpr double PI = 3.14;

    int n;

    cin >> n;

    auto input = views::iota(0, n) | views::transform([](auto) {
        point p;
        cin >> p.x >> p.y;
        return p;
    });

    vector<point> points(ranges::begin(input), ranges::end(input));

    auto center = circle_utils::minimumCircle(points);

    cout.precision(2);
    cout.setf(ios_base::fixed);

    cout << center.c.x << ' ' << center.c.y << ' ' << center.r << ' ' << 8.0 * PI * center.r << '\n';

    return 0;
}