#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

struct Point {
	int x, y, z;
	Point() {}
	Point(int _x, int _y, int _z) : x {_x}, y {_y}, z {_z} {}
};


Point cross(Point a, Point b) {
	int ax = a.x, ay = a.y, az = a.z;
	int bx = b.x, by = b.y, bz = b.z;
	return Point((ay * bz - az * by), -(ax * bz - az * bx), (ax * by - ay * bx));
}

i64 dot(Point a, Point b) {
	int ax = a.x, ay = a.y, az = a.z;
	int bx = b.x, by = b.y, bz = b.z;
	return (i64)ax * bx + (i64)ay * by + (i64)az * bz;
}

bool operator==(Point a, Point b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

Point operator-(Point a, Point b) {
	return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

void solve() {
	int n, ans = 0;
	cin >> n;
	
	vector<Point> p(n);

	for(int i = 0; i < n; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		p[i] = Point(x, y, z);
	}

	for(int i = 0; i < n; ++i) {
		int cnt = 0;

		// pi = pj
		for(int j = 0; j < n; ++j) cnt += p[i] == p[j];
		ans = max(ans, cnt);

		// colinear
		for(int j = 0; j < n; ++j) {
			if(p[i] == p[j]) continue;
			Point u = p[j] - p[i];
			int cnt = 0;
			for(int k = 0; k < n; ++k)
				cnt += cross(u, p[k] - p[i]) == Point(0, 0, 0);
			ans = max(ans, cnt);
		}

		// plano
		for(int j = i + 1; j < n; ++j) {
			if(p[i] == p[j]) continue;
			for(int k = j + 1; k < n; ++k) {
				if(p[i] == p[k] || p[j] == p[k]) continue;
				Point a = cross(p[j] - p[i], p[k] - p[i]);
				if(a == Point(0, 0, 0)) continue;
				int cnt = 0;
				for(int l = 0; l < n; ++l) cnt += dot(a, p[l] - p[i]) == 0;
				ans = max(ans, cnt);
			}
		}
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
