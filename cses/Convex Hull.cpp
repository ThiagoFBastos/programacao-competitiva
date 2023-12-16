#include "bits/stdc++.h"
 
using namespace std;
 
#define X first
#define Y second
 
using pt = pair<int, int>;
using ll = long long;
 
ll det(pt a, pt b, pt c) {
	return 1ll * b.X * c.Y - 1ll * b.Y * c.X
		  -1ll * a.X * (c.Y - b.Y)
		  +1ll * a.Y * (c.X - b.X);
}
 
auto convex_hull(vector<pt>& pol) {
	int n = size(pol);
	vector<pt> U, L;
 
	sort(pol.begin(), pol.end());
	U.emplace_back(pol[0]);
	L.emplace_back(pol[0]);
 
	for(int i = 1; i < n; ++i) {
 
		while((int)size(U) >= 2) {
			int m = size(U);
			if(det(U[m - 2], U[m - 1], pol[i]) <= 0) break;
			U.pop_back();
		}
 
		while((int)size(L) >= 2) {
			int m = size(L);
			if(det(L[m - 2], L[m - 1], pol[i]) >= 0) break;
			L.pop_back();
		}
 
		U.emplace_back(pol[i]);
		L.emplace_back(pol[i]);
	}
 
	for(int k = (int)L.size() - 2; k > 0; --k) U.emplace_back(L[k]);
	return U;
}
 
void solve() {
	int n;
	cin >> n;
	vector<pt> pol(n);
	for(auto& [x, y] : pol) cin >> x >> y;
	auto S = convex_hull(pol);
	cout << size(S) << '\n';
	for(auto [x, y] : S) cout << x << ' ' << y << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
