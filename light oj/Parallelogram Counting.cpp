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
	int x, y;

	point() {x = y = 0;}
	point(int _x, int _y) : x {_x}, y {_y} {}

	i64 square_norm() const {
		return 1ll * x * x + 1ll * y * y;
	}

	bool operator<(point other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator==(point other) const {
		return x == other.x && y == other.y;
	}

	point operator+(point other) const {
		return {x + other.x, y + other.y};
	}

	point operator-(point other) const {
		return {x - other.x, y - other.y};
	}

	point operator*(int k) const {
		return {x * k, y * k};
	}

	point operator-() const {
		return {-x, -y};
	}
};

i64 inner(point p1, point p2) {
	return (i64)p1.x * p2.x + (i64)p1.y * p2.y;
}

i64 cross(point p1, point p2) {
	return (i64)p1.x * p2.y - (i64)p1.y * p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q - p, r - p) > 0;
}

bool cw(point p, point q, point r) {
	return cross(q - p, r - p) < 0;
}

bool collinear(point p, point q, point r) {
	return cross(p - q, r - p) == 0;
}

bool between(point p, point q, point r) {
	return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

bool parallel(point a, point b) {
	return cross(a, b) == 0;
}

int cmp_frac(i64 x, i64 y, int cte) {
	if(x < 0 && y < 0) x *= -1, y *= -1;
	if(x < 0 || y < 0) x = -abs(x), y = abs(y);
	if(x < cte * y) return -1;
	return x == cte * y ? 0 : 1;
}

bool segIntersects(point a, point b, point p, point q) {
	if(parallel(a - b, p - q))
		return between(a, p, b) || between(a, q, b) || between(p, a, q) || between(p, b, q);

	point ba = b - a, qp = q - p, pa = p - a;

	i64 det = cross(-ba, qp);
	i64 detx = cross(-pa, qp);
	i64 dety = cross(ba, pa);

	return !(cmp_frac(detx, det, 0) == -1 || cmp_frac(detx, det, 1) == 1 || cmp_frac(dety, det, 0) == -1 || cmp_frac(dety, det, 1) == 1);
}

struct compare {
	bool operator()(const point& a, const point& b) const {
		if((a.y >= 0) != (b.y >= 0)) return (a.y >= 0) < (b.y >= 0);		
		return cross(a, b) > 0 || (cross(a, b) == 0 && a.square_norm() < b.square_norm());
	}
};

int tcase = 1;

i64 count(vector<point>& v) {
	int lo = 0;
	i64 cnt = 0;

	sort(all(v), compare());

	for(int i = 0; i < (int)v.size(); ++i) {
		if(cross(v[lo], v[i]) || v[lo].square_norm() != v[i].square_norm()) {
			int n = i - lo;
			cnt += n * (n - 1ll) / 2;
			lo = i;
		}
	}

	int n = (int)v.size() - lo;

	cnt += n * (n - 1ll) / 2;

	return cnt;
}

void solve() {
	int n;

	cin >> n;

	vector<point> pt(n), segs;

	for(auto& [x, y] : pt) cin >> x >> y;

	i64 paralelograms = 0;

	for(int i = 0; i < n; ++i) {
		vector<point> aux;

		for(int j = 0; j < n; ++j) {
			if(i == j) continue;

			auto du = pt[j] - pt[i];

			if(du.x < 0 || (!du.x && du.y < 0)) du = -du;
 			
			aux.pb(du);
			if(j > i) segs.pb(du);
		}

		paralelograms -= count(aux);
	}

	paralelograms += count(segs);

	cout << "Case " << tcase++ << ": " << paralelograms / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}