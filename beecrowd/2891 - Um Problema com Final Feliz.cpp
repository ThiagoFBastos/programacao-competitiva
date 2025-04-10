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

int area(vector<pt>& p) {
	int ans {}, n = size(p);
	
	for(int i = 0; i < n; ++i) {
		int k = i + 1;
		if(k >= n) k -= n;
		ans += p[i].X * p[k].Y - p[i].Y * p[k].X;
	}
	
	return abs(ans);
}

bool cmp(vector<pt>& a, vector<pt>& b) {
	auto B = b;
	sort(B.begin(), B.end());
	return a == B; 
}

void solve() {
	vector<pt> p(5), a(4);
	int v {};
	
	for(int i = 0; i < 5; ++i) cin >> p[i].X >> p[i].Y;
	
	sort(p.begin(), p.end());
	
	if(count(p.begin(), p.end(), make_pair(0, 0)) == 5) exit(0);
	
	for(int k = 0; k < 5; ++k) {
		int i = 0;
		for(int j = 0; j < 5; ++j) {
			if(k == j) continue;
			a[i++] = p[j];
		}
		auto b = convex_hull(a);
		if(cmp(a, b)) v = max(v, area(b));
	}
	
	cout << v / 2 << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(;;) solve();
	return 0;
}