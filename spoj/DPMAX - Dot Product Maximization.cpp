#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

using pt = pair<ld, ld>;

const ld eps = 1e-9;

#define x first
#define y second

ld cross(pt a, pt b) {
	return a.x * b.y - a.y * b.x;
}

ld dot(pt a, pt b) {
	return a.x * b.x + a.y * b.y;
}

ld det(pt a, pt b, pt c) {
	return cross(make_pair(b.x-a.x,b.y-a.y), make_pair(c.x-a.x,c.y-a.y));
}

vector<pt> upperHull(vector<pt>& a) {
	int n = a.size();
	vector<pt> upper;
	
	auto p = a;
	sort(p.begin(), p.end());
	
	upper.push_back(p[0]);
	
	for(int i = 1; i < n; ++i) {
		while((int)upper.size() >= 2) {
			int n = upper.size();
			if(det(upper[n - 2], upper[n - 1], p[i]) < -eps) break;
			upper.pop_back();
		}
		upper.push_back(p[i]);
	}
	
	return upper;
}

vector<pt> lowerHull(vector<pt>& a) {
	int n = a.size();
	vector<pt> lower;
	
	auto p = a;
	sort(p.begin(), p.end());
	
	lower.push_back(p[0]);
	
	for(int i = 1; i < n; ++i) {
		while((int)lower.size() >= 2) {
			int n = lower.size();
			if(det(lower[n - 2], lower[n - 1], p[i]) > eps) break;
			lower.pop_back();
		}
		lower.push_back(p[i]);
	}
	
	return lower;
}

void solve() {
	int n;

	cin >> n;

	vector<pt> a(n);

	for(int i = 0; i < n; ++i) {
		ld x, y;
		cin >> x >> y;
		a[i] = {x, y};
	}

	auto u = upperHull(a);
	auto l = lowerHull(a);

	auto query = [](vector<pt>& p, pt q) {
		int l = 0, r = (int)p.size() - 1;
		ld ans = LLONG_MIN;
		while(l + 2 < r) {
			int lo = l + (r - l) / 3;
			int hi = r - (r - l) / 3;
			if(dot(q, p[lo]) < dot(q, p[hi])) l = lo;
			else r = hi;
		}
		while(l <= r) ans = max(ans, dot(q, p[l++]));
		return ans;
	};

	for(auto k : a) cout << fixed << setprecision(3) << max(query(l, k), query(u, k)) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
 