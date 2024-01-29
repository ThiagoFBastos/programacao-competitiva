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

const int inf = 1e9;

void solve() {
	int r, c, n;
	cin >> r >> c >> n;
	
	vector<int> lo(r, inf), hi(r, -inf);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		lo[x] = min(lo[x], y);
		hi[x] = max(hi[x], y);
	}
	
	vector<int> loy, hiy;
	
	for(int x = 0; x < r; ++x) {
		if(lo[x] > hi[x]) continue;
		loy.push_back(lo[x]);
		hiy.push_back(hi[x]);
	}
	
	sort(loy.begin(), loy.end());
	sort(hiy.begin(), hiy.end());
	
	i64 ans = LLONG_MAX, lo_sum = 0, hi_sum = 0;
	int k = 0, j = 0;
	
	for(int y : hiy) hi_sum += y;
	
	for(int z = 0; z < c; ++z) {
		i64 s = 0;
		
		while(j < (int)hiy.size() && hiy[j] <= z) hi_sum -= hiy[j++];
		while(k < (int)loy.size() && loy[k] <= z) lo_sum += loy[k++];
	
		s += hi_sum - (i64)((int)hiy.size() - j) * z;
		s += (i64)k * z - lo_sum;
		s <<= 1;
		s += r - 1;
		
		ans = min(ans, s);
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


