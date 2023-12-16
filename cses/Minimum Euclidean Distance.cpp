#include "bits/stdc++.h"
#define double long double
 
using namespace std;
 
#define X first
#define Y second
 
using pt = pair<int, int>;
using ll = long long;
 
const int inf = 1e9;
const ll linf = 8e18L + 100;
 
ll dist(pt a, pt b) {
	ll x = a.X - b.X, y = b.Y - a.Y;
	return x * x + y * y;
}
 
void solve() {
	int n, k = 0;
	ll d = linf;;
 
	cin >> n;
 
	vector<pt> p(n);
	set<pt> S;
 
	for(auto& [x, y] : p) cin >> x >> y;
	sort(p.begin(), p.end());
 
	for(int i = 0; i < n; ++i) {
		auto& [x, y] = p[i];
		swap(x, y);
		double h = sqrt(d);
		for(; k < i && y - p[k].Y >= h; ++k) S.erase(p[k]);
		for(auto j = S.lower_bound({x - h, -inf}); j != S.end() && abs(j->first - x) < h; ++j)
			d = min(d, dist(p[i], *j));
		S.insert(p[i]);
	}
 
	cout << d << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
