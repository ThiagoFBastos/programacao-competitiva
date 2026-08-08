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

int n, q, _x0, _y0;
	
int get_max_dist(int x1, int y1, int x2, int y2) {
	int x, y;
	x = abs(_x0 - x1) > abs(_x0 - x2) ? x1 : x2;
	y = abs(_y0 - y1) > abs(_y0 - y2) ? y1 : y2;
	return abs(x - _x0) + abs(y - _y0);	
}

int get_min_dist(int x1, int y1, int x2, int y2) {
	int x, y;
	if(x2 <= _x0) x = x2;
	else if(_x0 <= x1) x = x1;
	else x = _x0;
	if(y2 <= _y0) y = y2;
	else if(_y0 <= y1) y = y1;
	else y = _y0;
	return abs(x - _x0) + abs(y - _y0);	
}

void solve() {
	
	cin >> n >> q >> _x0 >> _y0;
	
	vector<int> L, R;
	
	for(int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		
		cin >> x1 >> y1 >> x2 >> y2;
		
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		
		R.push_back(get_max_dist(x1, y1, x2, y2));
		L.push_back(get_min_dist(x1, y1, x2, y2));
	}
	
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	
	while(q--) {
		int d;
		cin >> d;
		int left = lower_bound(R.begin(), R.end(), d) - R.begin();
		int right = n - (upper_bound(L.begin(), L.end(), d) - L.begin());
		cout << n - left - right << '\n';
	}
	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}