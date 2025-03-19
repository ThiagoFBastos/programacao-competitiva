#pragma GCC optimize("O3")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4")

#include "bits/stdc++.h"

using namespace std;

const int inf = 1e9, N = 2e3 + 1;

int t, pre[N][N];

void solve() {
	int dx, dy, n, q;
	
	cin >> dx >> dy >> n >> q;
	
	if(dx + dy + n + q == 0) exit(0);
	
	int r = dx + dy, c = dx + dy;
	
	vector<pair<int, int>> p(n);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x + y, dy + x - y};
	}
	
	sort(p.begin(), p.end());
	
	int i = 0;
	
	for(int x = 1; x <= r; ++x) {
		for(int y = 1; y <= c; ++y) {
			int g = 0;
			if(i < n && p[i] == make_pair(x, y)) g = 1, ++i;
			pre[x][y] = g + pre[x - 1][y] + pre[x][y - 1] - pre[x - 1][y - 1];
		}
	}
		
	cout << "Case " << ++t << ":\n";
	
	while(q--) {
		int d;
		
		cin >> d;
		
		auto ans = make_tuple(0, -inf, -inf);
		
		for(int x = 1; x <= dx; ++x) {
			for(int y = 1; y <= dy; ++y) {
				int _x = x + y, _y = dy + x - y;
				int x1 = min(_x + d, r), y1 = min(_y + d, c), x0 = max(1, _x - d), y0 = max(1, _y - d);
				int cnt = pre[x1][y1] - pre[x1][y0 - 1] - pre[x0 - 1][y1] + pre[x0 - 1][y0 - 1];
				ans = max(ans, make_tuple(cnt, -y, -x));
			}
		}
		
		auto [v, y, x] = ans;
		cout << v << " (" << -x << ',' << -y << ")\n";
	}
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(true) solve();
	return 0;
}