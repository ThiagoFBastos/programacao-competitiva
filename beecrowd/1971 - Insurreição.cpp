#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

#define X first
#define Y second

using pt = pair<int, int>;

int det(pt a, pt b, pt c) {
	return (b.X * c.Y - b.Y * c.X)
	 	 - a.X * (c.Y - b.Y)
	 	 + a.Y * (c.X - b.X);
}

bool ccw(pt a, pt b, pt c) {
	return det(a, b, c) > 0;
}

bool cw(pt a, pt b, pt c) {
	return det(a, b, c) < 0;
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

bool inside(vector<pt>& p, pt q) {
	int cnt = 0, n = size(p);
	for(int i = 0; i < n; ++i) cnt += det(q, p[i], p[(i + 1) % n]) >= 0;
	return cnt == n;
}

void solve() {
	int x, y;
	vector<pt> p(4);
	
	for(int i = 0; i < 4; ++i) cin >> p[i].X >> p[i].Y;
	
	cin >> x >> y;
	
	p = convex_hull(p);
	
	if((int)size(p) >= 3 && inside(p, {x, y})) {
		cout << "\\O/" << endl;
		cout << " | " << endl;
		cout << "/ \\" << endl;
	} else {
		cout << " O>" << endl;
		cout << "<| " << endl;
		cout << "/ >" << endl;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}