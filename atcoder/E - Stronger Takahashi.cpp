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

using T = tuple<int, int, int>;

ii mov[] = {
	{1, 0},
	{-1, 0},
	{0, -1},
	{0, 1}
};

void solve() {
	int h, w;

	cin >> h >> w;

	vector<string> g(h);
	priority_queue<T> pq;	
	auto dist = vector<vector<int>>(h, vector<int>(w, -1));

	for(auto& s : g) cin >> s;

	pq.emplace(0, 0, 0);

	while(!pq.empty()) {
		auto [c, x, y] = pq.top();

		pq.pop();

		c *= -1;

		if(dist[x][y] != -1) continue;

		dist[x][y] = c;
       
		for(auto [dx, dy] : mov) {
			int _x = x + dx, _y = y + dy;

			if(_x < 0 || _y < 0 || _x >= h || _y >= w || dist[_x][_y] != -1) continue;
	
			if(g[_x][_y] == '.') {
				pq.emplace(-c, _x, _y);
				continue;
			}

			for(int dx = -1; dx <= 1; ++dx) {
				for(int dy = -1; dy <= 1; ++dy) {
					int __x = _x + dx, __y = _y + dy;
					if(__x < 0 || __y < 0 || __x >= h || __y >= w || dist[__x][__y] != -1) continue;
					pq.emplace(-1 - c, __x, __y);				
				}
			}
		}
	}

	cout << dist[h - 1][w - 1] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
