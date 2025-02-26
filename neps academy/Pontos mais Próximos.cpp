#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<i64, i64>;

i64 D(ii a, ii b) {
	i64 x = b.first - a.first, y = b.second - a.second;
	return x * x + y * y;
}

void solve() {
	int n, k = 0;
	i64 dist = LLONG_MAX;
	
	cin >> n;
	
	vector<ii> p(n);
	set<ii> S;
	
	for(auto& [x, y] : p) cin >> x >> y;
	
	sort(p.begin(), p.end());
	
	for(int i = 0; i < n; ++i) {
		auto& [x, y] = p[i];
		
		swap(x, y);
		
		i64 h = sqrt(dist);
		
		for(; k < i && y - p[k].second > h; ++k) S.erase(p[k]);
		
		for(auto j = S.lower_bound(make_pair(x - h, 0)); j != S.end() && abs(j->first - x) <= h; ++j)
			dist = min(dist, D(p[i], *j));
		
		S.insert(p[i]);
	}
	
	cout << fixed << setprecision(6) << sqrt(dist) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}