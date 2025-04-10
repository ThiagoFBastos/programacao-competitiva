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

	double norm() const {
		return hypot(x, y);
	}

	i64 square_norm() const {
		return 1ll * x * x + 1ll * y * y;
	}

	bool operator<(point other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator>(point other) const {
		return x > other.x || (x == other.x && y > other.y);
	}

	bool operator<=(point other) const {
		return x < other.x || (x == other.x && y <= other.y);
	}

	bool operator>=(point other) const {
		return x > other.x || (x == other.x && y >= other.y);
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

	point& operator*=(int k) {
		x *= k;
		y *= k;
		return *this;
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

double distToSeg(point p, point A, point B) {
	if(inner(p - A, B - A) <= 0) return (p-A).norm();
	if(inner(p - B, A - B) <= 0) return (p-B).norm();
	return abs(cross(p-A,B-A)) / (B-A).norm(); 
}

double distSegs(point p, point q, point A, point B) {
	if(segIntersects(p, q, A, B)) return 0;
	double dAB = min(distToSeg(p, A, B), distToSeg(q, A, B));
	double dpq = min(distToSeg(A, p, q), distToSeg(B, p, q));
	return min(dAB, dpq);
}

struct uf {
	vector<int> par, rank, sz;
	
	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		return v == par[v] ? v : par[v] = findSet(par[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);
		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		par[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];
		return true;
	}
};

void solve() {
	int n;

	cin >> n;

	vector<pair<point, point>> s(n);
	uf dsu(n);
	vector<tuple<double, int, int>> w;
	double ans = 0;

	for(auto& [p, q] : s) cin >> p.x >> p.y >> q.x >> q.y;

	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			w.pb({distSegs(s[i].fi,s[i].sc,s[j].fi,s[j].sc),i,j});
	
	sort(all(w));

	for(auto [d, u, v] : w) if(dsu.join(u, v)) ans += d;

	cout << (int)ceil(ans) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}