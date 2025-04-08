#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

#define double long double
#define X first
#define Y second

const double eps = 1e-9L;

using pt = pair<double, double>;

double det(pt a, pt b, pt c) {
	return (b.X * c.Y - b.Y * c.X)
	 	 - a.X * (c.Y - b.Y)
	 	 + a.Y * (c.X - b.X);
}

bool ccw(pt a, pt b, pt c) {
	return det(a, b, c) > eps;
}

bool cw(pt a, pt b, pt c) {
	return det(a, b, c) < -eps;
}

auto convex_hull(vector<pt>& p) {
	vector<pt> A, B;
	
	sort(p.begin(), p.end());
	
	A.emplace_back(p[0]);
	B.emplace_back(p[0]);
	
	for(int i = 1; i < (int)size(p); ++i) {
		while((int)size(A) > 1 && !cw(A[(int)A.size() - 2], A[(int)A.size() - 1], p[i])) A.pop_back();
		while((int)size(B) > 1 && !ccw(B[(int)B.size() - 2], B[(int)B.size() - 1], p[i])) B.pop_back();
		A.emplace_back(p[i]);
		B.emplace_back(p[i]);
	}
	
	reverse(A.begin(), A.end());
	for(int i = 1; i < (int)size(B) - 1; ++i) A.emplace_back(B[i]);
	
	return A;
}

double area(vector<pt>& p) {
	double ans {};
	int n = size(p);
	
	for(int i = 0; i < n; ++i) {
		int k = i + 1;
		if(k >= n) k -= n;
		ans += p[i].X * p[k].Y - p[i].Y * p[k].X;
	}
	
	return 0.5 * abs(ans);
}

void solve() {
	int n, x0, y0, z0;
	
	cin >> n >> x0 >> y0 >> z0;
	
	if(!n) exit(0);
	
	vector<pt> p(n);
	
	for(int i = 0; i < n; ++i) {
		int x1, y1, z1;
		double t;
		cin >> x1 >> y1 >> z1;
		t = -z0 / (double)(z1 - z0);
		p[i] = {x0 + t * (x1 - x0) , y0 + t * (y1 - y0)};
	}
	
	auto pol = convex_hull(p);
	
	cout << area(pol) << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	for(;;) solve();
	return 0;
}