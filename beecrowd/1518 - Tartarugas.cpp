#include "bits/stdc++.h"

using namespace std;

const int inf = 1e9;

int dist(int xdest, int ydest, int x, int y) {
	int a = abs(xdest - x), b = abs(ydest - y);
	if(a > b) swap(a, b);
	return a + (b - a + 1) / 2;
}

bool consegue(int xdest, int ydest, int x1, int y1, int x2, int y2) {
	return abs(x1 - xdest) + abs(y1 - ydest) >= dist(xdest, ydest, x2, y2);
}

void solve() {
	int x, y, p[3][2];
	char c[3];
	
	cin >> x >> y;
	
	if(!(x || y)) exit(0);
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 2; ++j) cin >> p[i][j];
		cin >> c[i];
	}
		
	vector<int> P {0, 1, 2};
	int t = inf;
	
	do
	{
		int T = 0, x0 = x, y0 = y;
		for(int k : P) {
			int _x = p[k][0], _y = p[k][1];
			if(c[k] == 'C') {
				_y += T;
				int L = _y, R = inf;
				while(L < R) {
					int mid = (L + R) / 2;
					if(consegue(_x, mid, _x, _y, x0, y0)) R = mid;
					else L = mid + 1;
				}
				T += R - _y;
				x0 = _x, y0 = R;
			} else {
				_x += T;
				int L = _x, R = inf;
				while(L < R) {
					int mid = (L + R) / 2;
					if(consegue(mid, _y, _x, _y, x0, y0)) R = mid;
					else L = mid + 1;
				}
				T += R - _x;
				x0 = R, y0 = _y;
			}
		}
		
		t = min(t, T);
		
	} while(next_permutation(P.begin(), P.end()));
	
	cout << t << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(;;) solve();
	return 0;
}