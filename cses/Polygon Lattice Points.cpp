#include "bits/stdc++.h"
 
using namespace std;
 
#define X first
#define Y second
 
using pt = pair<int, int>;
using ll = long long;
 
ll cross(pt a, pt b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X;
}
 
ll area(vector<pt>& pol) {
	ll ans = 0;
	int n = size(pol);
	for(int i = 0; i < n; ++i)
		ans += cross(pol[i], pol[(i + 1) % n]);
	return abs(ans);
}
 
ll cnt_points(pt a, pt b) {
	return gcd(abs(a.X - b.X), abs(a.Y - b.Y));
}
 
ll boundary_points(vector<pt>& pol) {
	ll cnt = 0;
	int n = size(pol);
	for(int i = 0; i < n; ++i)
		cnt += cnt_points(pol[i], pol[(i + 1) % n]);
	return cnt;
}
 
void solve() {
	int n;
	cin >> n;
	vector<pt> pol(n);
	for(auto& [x, y] : pol) cin >> x >> y;
	ll A = area(pol);
	ll b = boundary_points(pol);
	ll i = (A + 2 - b) / 2;
	cout << i << ' ' << b << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
