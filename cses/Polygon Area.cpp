#include "bits/stdc++.h"
 
using namespace std;
 
#define X first
#define Y second
using pt = pair<int, int>;
 
auto cross(pt a, pt b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X;
}
 
auto area(vector<pt>& pol) {
	int n = size(pol);
	auto ans = 0LL;
	for(int i = 0; i < n; ++i)
		ans += cross(pol[i], pol[(i + 1) % n]);
	return abs(ans);
}
 
void solve() {
	int n;
	cin >> n;
	vector<pt> pol(n);
	for(auto& [x, y] : pol) cin >> x >> y;
	cout << area(pol) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
