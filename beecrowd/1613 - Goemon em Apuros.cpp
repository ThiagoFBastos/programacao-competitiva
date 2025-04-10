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

struct Event {
	point p;
	int type;
};

bool operator<(Event e1, Event e2) {
	if(cross(e1.p, e2.p)) return cross(e1.p, e2.p) > 0;
	return e1.type < e2.type;
}

void solve() {
	int xc, yc, n, m, ans = 0;

	cin >> xc >> yc >> n;

	vector<Event> e;

	while(n--) {
		int y0, y1;
		cin >> y0 >> y1;
		e.pb({point(0, y0) - point(xc, yc), 1});
		e.pb({point(0, y1) - point(xc, yc), -1});
	}

	cin >> m;

	while(m--) {
		int x, y;
		cin >> x >> y;
		e.pb({point(x, y) - point(xc, yc), 0});
	}

	sort(all(e));

	int active = 0;

	for(auto& v : e) {
		if(v.type == -1) ++active;
		else if(v.type == 1) --active;		
		else ans += !!active;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}