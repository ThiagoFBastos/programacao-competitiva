#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

const double eps = 1e-9;

using ii = pair<int, int>;
using pt = pair<double, double>;

int n, depth, litres, m;
vector<ii> p;
vector<pt> polygon;

double area() { 
	double ans = 0;
	for(int k = 0; k < m; ++k) {
		int i = k + 1;
		if(i >= m) i -= m;
		ans += polygon[k].first * polygon[i].second - polygon[k].second * polygon[i].first;
	}
	return abs(ans) * 0.5;
}

pt findPoint(ii a, ii b, double h) {
	int dx = b.first - a.first, dy = b.second - a.second;
	double t = (h - a.second) / (double)dy;
	return {a.first + dx * t, a.second + dy * t};
}

void findPolygon(double h) {
	m = 0;
	for(int i = 0; i < n; ++i) {
		int k = i + 1;
		if(k >= n) k -= n;
		if(p[i].second <= h) {
			polygon[m++] = make_pair<double>(p[i].first, p[i].second);
			if(p[k].second > h) polygon[m++] = findPoint(p[i], p[k], h);
		} else if(p[k].second < h) polygon[m++] = findPoint(p[i], p[k], h);
	}
}

bool this_height(double h) {
	findPolygon(h);
	return litres - area() * depth / 1e3 <= eps;
}

void solve() {
	
	cin >> n >> depth >> litres;
	
	p.resize(n);
	polygon.resize(n);
	
	double L = 0, R = 0;
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
		R = max<double>(R, y); 
	}
	
	for(int k = 0; k < 64; ++k) {
		double mid = (L + R) / 2;
		if(this_height(mid)) R = mid;
		else L = mid;
	}
	
	cout.precision(2);
	cout << fixed << R << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}



