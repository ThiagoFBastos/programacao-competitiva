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

std::mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

using pt = pair<i64, i64>;

i64 det(pt a, pt b, pt c) {
	return b.first * c.second - b.second * c.first
		  - a.first * (c.second - b.second) 
		  + a.second * (c.first - b.first);
}

auto convexHull(vector<pt>& p) {
	int n = p.size();
	vector<pt> upper, lower;
	
	sort(p.begin(), p.end());
	
	upper.push_back(p[0]);
	lower.push_back(p[0]);
	
	for(int i = 1; i < n; ++i) {
		while((int)upper.size() >= 2) {
			int n = upper.size();
			if(det(upper[n - 2], upper[n - 1], p[i]) < 0) break;
			upper.pop_back();
		}
		
		while((int)lower.size() >= 2) {
			int n = lower.size();
			if(det(lower[n - 2], lower[n - 1], p[i]) > 0) break;
			lower.pop_back();
		}
		
		upper.push_back(p[i]);
		lower.push_back(p[i]);
	}
	
	for(int k = (int)lower.size() - 2; k > 0; --k) upper.push_back(lower[k]);
	return upper;
}

i64 area(vector<pt> p) {
	auto P = convexHull(p);
	i64 ans = 0;
	int n = P.size();
	for(int i = 0; i < n; ++i) {
		i64 x1 = P[i].first, y1 = P[i].second;
		i64 x2 = P[(i+1)%n].first, y2 = P[(i+1)%n].second;
		ans += (i64)x1 * y2 - (i64)x2 * y1;
	}
	return abs(ans);
}

void solve() {

	int T1, T2, t1, t2;
	
	cin >> T1 >> T2 >> t1 >> t2;

	vector<pt> p, a;
	vector<tuple<int, int, int>> v;

	v.emplace_back(-1, 1, t1);
	v.emplace_back(1, -1, t2);
	v.emplace_back(1, 0, 0);
	v.emplace_back(0, 1, 0);
	v.emplace_back(1, 0, T1);
	v.emplace_back(0, 1, T2);
	
	for(int i = 0; i < (int)v.size(); ++i) {
		for(int j = i + 1; j < (int)v.size(); ++j) {
			int a1, b1, c1, a2, b2, c2;
			
			tie(a1, b1, c1) = v[i];
			tie(a2, b2, c2) = v[j];
			
			i64 det = (i64)a1 * b2 - (i64)a2 * b1;
			if(!det) continue;
			
			i64 detx = (i64)c1 * b2 - (i64)c2 * b1;
			i64 dety = (i64)a1 * c2 - (i64)a2 * c1;
			
			i64 x = detx / det, y = dety / det;
			
			if(x - y > t2 || y - x > t1 || x > T1 || y > T2 || x < 0 || y < 0) continue;
			
			p.emplace_back(x, y);
		}
	}

	cout << fixed << setprecision(10) << area(p) / double(2ll * T1 * T2) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
