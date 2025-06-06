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

const double eps = 1e-10;

template<class T>
struct point {
	T x, y;
	
	point() {x = y = 0;}
	point(T x, T y) : x {x}, y {y} {}
	
	point operator+(point p) {
		p.x += x;
		p.y += y;
		return p;
	}
	
	point operator-(point p) {
		p.x -= x;
		p.y -= y;
		return p;
	}
	
	point operator*(T alpha) {
		return {x * alpha, y * alpha};
	}
	
	point operator/(T alpha) {
		return {x / alpha, y / alpha};
	}
	
	point& operator+=(point p) {
		x += p.x;
		y += p.y;
		return *this;
	}
	
	point& operator-=(point p) {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	
	point& operator*=(T alpha) {
		x *= alpha;
		y *= alpha;
		return *this;
	}
	
	point& operator/=(T alpha) {
		x /= alpha;
		y /= alpha;
		return *this;
	}
	
	T cross(point p) {
		return x * p.y - y * p.x;
	}
	
	T dot(point p) {
		return x * p.x + y * p.y;
	}
	
	bool operator==(point p) {
		return fabs(x - p.x) < (T)eps && fabs(y - p.y) < (T)eps;
	}
	
	bool operator!=(point p) {
		return !(*this == p);
	}
	
	point operator-() {
		return {-x, -y};
	}
};

template<class T>
point<double> operator*(point<T> p, double alpha) {
	return {p.x * alpha, p.y * alpha};
}

template<class T>
point<double> operator/(point<T> p, double alpha) {
	return {p.x / alpha, p.y / alpha};
}

template<class T>
double dist(point<T> a, point<T> b) {
	return hypot(a.x - b.x, a.y - b.y);
}

template<class T>
double abs(point<T> p) {
	return hypot(p.x, p.y);
}

template<class T>
point<double> norm(point<T> p) {
	double d = abs(p);
	return {p.x / d, p.y / d};
}

template<class T>
point<double> rotate(point<T> p, double theta) {
	return {p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta)};
}

template<class T>
T det(point<T> a, point<T> b, point<T> c) {
	return b.x * c.y - b.y * c.x
	      -a.x * (c.y - b.y)
	      +a.y * (c.x - b.x);
}

template<class T>
bool cw(point<T> a, point<T> b, point<T> c) {
	return det(a, b, c) < 0;
}

template<class T>
bool ccw(point<T> a, point<T> b, point<T> c) {
	return det(a, b, c) > 0;
}

template<class T>
ostream& operator<<(ostream& os, point<T> p) {
	os << p.x << ' ' << p.y;
	return os;
}

i64 count_border_points(vector<point<i64>>& p) {
	i64 ans {};
	int n = size(p);
	for(int i = 0; i < n; ++i) {
		int k = (1 + i) % n;
		ans += gcd(abs(p[i].x - p[k].x), abs(p[i].y - p[k].y));
	}
	return ans;
}

i64 area(vector<point<i64>>& p) {
	i64 ans {};
	int n = size(p);
	for(int i = 0; i < n; ++i) ans += p[i].cross(p[(i + 1) % n]);
	return abs(ans);
}

void solve() {
	int n;
	cin >> n;
	vector<point<i64>> p(n);
	for(auto& [x, y] : p) cin >> x >> y;
	cout << (area(p) - count_border_points(p) + 2) / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}