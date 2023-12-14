#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
int n, radius;
 
bool getSecs(int a, int b, int c, int d, ld& s1, ld& s2) {
	i64 C = (i64)a * a + (i64)b * b - (i64)radius * radius;
	i64 B = 2 * ((i64)a * c + (i64)b * d);
	i64 A = (i64)c * c + (i64)d * d;
	__int128 D = (__int128)B * B - (__int128)4 * A * C;
	if(D < 0) return false;
	ld delta = sqrt((ld)D);
	s1 = (-B - delta) / (2.0L * A);
	s2 = (-B + delta) / (2.0L * A); 
	return true;
}
 
void solve() {
	cin >> n >> radius;
 
	set<pair<i64, int>> sweep;
	int opening = 0, ans = 0;
 
	for(int i = 1; i <= n; ++i) {
		int a, b, c, d;
		ld s1, s2;
 
		cin >> a >> b >> c >> d;
 
		if(!getSecs(a, b, c - a, d - b, s1, s2)) continue;
		
		i64 l = max(0.0L, ceil(s1)), r = floor(s2); 
		
		if(l > r) continue;
 
		sweep.emplace(l, -i);
		sweep.emplace(r, i);
	}
 
	for(auto [x, k] : sweep) {
		opening += k < 0 ? 1 : -1;
		ans = max(ans, opening);
	}
 
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
