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
	
	T sz() {
		return x * x + y * y;	
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

int quad(point<i64> p) {
	if(p.x >= 0 && p.y >= 0) return 0;
	else if(p.x <= 0 && p.y >= 0) return 1;
	else if(p.x <= 0 && p.y <= 0) return 2;
	return 3; 
}

bool cmp(point<i64> a, point<i64> b) {
	if(quad(a) != quad(b)) return quad(a) < quad(b);
	i64 cross = a.cross(b);
	return cross > 0 || !cross && a.sz() < b.sz();
}

void solve() {
	int n;
	cin >> n;
	vector<point<i64>> a(n);
	for(auto& [x, y] : a) cin >> x >> y;
	sort(a.begin(), a.end(), cmp);
	for(auto [x, y] : a) cout << x << ' ' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}