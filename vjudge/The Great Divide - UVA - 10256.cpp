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

	bool operator<(point other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator==(point other) const {
		return x == other.x && y == other.y;
	}

	point operator+(point other) {
		return {x + other.x, y + other.y};
	}

	point operator-(point other) {
		return {x - other.x, y - other.y};
	}

	point operator*(int k) {
		return {x * k, y * k};
	}
};

int inner(point p1, point p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

int cross(point p1, point p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

int ccw(point p, point q, point r) {
	return cross(q - p, r - p) > 0;
}

int cw(point p, point q, point r) {
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

int cmp_frac(int x, int y, int cte) {
	if(x < 0 && y < 0) x *= -1, y *= -1;
	if(x < 0 || y < 0) x = -abs(x), y = abs(y);
	if(x < cte * y) return -1;
	return x == cte * y ? 0 : 1;
}

bool segIntersects(point a, point b, point p, point q) {
	if(parallel(a - b, p - q))
		return between(a, p, b) || between(a, q, b) || between(p, a, q) || between(p, b, q);

	point ba = b - a, qp = q - p, pa = p - a;

	int det = -ba.x * qp.y + ba.y * qp.x;
	int detx = -pa.x * qp.y + pa.y * qp.x;
	int dety = 	ba.x * pa.y - ba.y * pa.x;

	return !(cmp_frac(detx, det, 0) == -1 || cmp_frac(detx, det, 1) == 1 || cmp_frac(dety, det, 0) == -1 || cmp_frac(dety, det, 1) == 1);
}

vector<point> convexHull(vector<point>& a) {
	int n = a.size();
	vector<point> upper, lower;
	
	auto p = a;
	sort(p.begin(), p.end());
	
	upper.push_back(p[0]);
	lower.push_back(p[0]);
	
	for(int i = 1; i < n; ++i) {
		while((int)upper.size() >= 2) {
			int n = upper.size();
			if(cw(upper[n - 2], upper[n - 1], p[i])) break;
			upper.pop_back();
		}
		
		while((int)lower.size() >= 2) {
			int n = lower.size();
			if(ccw(lower[n - 2], lower[n - 1], p[i])) break;
			lower.pop_back();
		}
		
		upper.push_back(p[i]);
		lower.push_back(p[i]);
	}
	
	for(int k = (int)lower.size() - 2; k > 0; --k) upper.push_back(lower[k]);
	return upper;
}

bool contains(vector<point>& poly, point p) {
	int n = poly.size(), t1 = 0, t2 = 0;	
	for(int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		t1 += cross(poly[i] - p, poly[j] - p) > 0;
		t2 += cross(poly[i] - p, poly[j] - p) < 0;
	}
	return max(t1, t2) == n;
}

void solve() {
	while(true) {
		int n, m;

		cin >> n >> m;

		if(n + m == 0) break;

		vector<point> a(n), b(m);

		for(auto& p : a) cin >> p.x >> p.y;
		for(auto& p : b) cin >> p.x >> p.y;

		auto A = convexHull(a);
		auto B = convexHull(b);

		bool no = contains(B, A[0]) || contains(A, B[0]);
		
		for(int i = 0; i < (int)A.size(); ++i) {
			int j = (i + 1) % (int)A.size();
			for(int k = 0; k < (int)B.size(); ++k) {
				int l = (k + 1) % (int)B.size();
				no = no || segIntersects(A[i], A[j], B[k], B[l]);
			}
		}

		cout << (no ? "No\n" : "Yes\n");
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}