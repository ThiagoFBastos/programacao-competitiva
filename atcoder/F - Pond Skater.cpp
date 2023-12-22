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

void solve() {
	int h, w, k;
	int x1, y1, x2, y2;

	cin >> h >> w >> k;	
	cin >> x1 >> y1 >> x2 >> y2;

	--x1, --y1, --x2, --y2;

	vector<string> g(h);
	vector<vector<int>> cost(h, vector<int>(w, -1));
	vector<vector<int>> cntR(h, vector<int>(w + 1, 0));
	vector<vector<int>> cntC(h + 1, vector<int>(w, 0));

	queue<ii> q;
	vector<set<int>> row(h), col(w);

	
	for(auto& s : g) cin >> s;

	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			cntR[i][j + 1] = cntR[i][j] + (g[i][j] == '@');
			cntC[i + 1][j] = cntC[i][j] + (g[i][j] == '@');
			row[i].insert(j);
			col[j].insert(i);
		}
	}

	
	row[x1].erase(y1);
	col[y1].erase(x1);

	q.emplace(x1, y1);
	cost[x1][y1] = 0;

	while(!q.empty()) {
		queue<ii> s;

		while(!q.empty()) {
			auto [x, y] = q.front();
			q.pop();
			
			auto lo = row[x].lower_bound(y);
			
			while(lo != row[x].begin() && y - *prev(lo) <= k && cntR[x][y + 1] - cntR[x][*prev(lo)] == 0) --lo;

			auto hi = lo;

			while(hi != row[x].end() && *hi - y <= k && cntR[x][*hi + 1] - cntR[x][y] <= 0) {
				int yt = *hi;
				s.emplace(x, yt);
				cost[x][yt] = 1 + cost[x][y];
				col[yt].erase(x);
				++hi;
			}
			
			row[x].erase(lo, hi);

			lo = col[y].lower_bound(x);

			while(lo != col[y].begin() && x - *prev(lo) <= k && cntC[x + 1][y] - cntC[*prev(lo)][y] == 0) --lo;

			hi = lo;

			while(hi != col[y].end() && *hi - x <= k && cntC[*hi + 1][y] - cntC[x][y] <= 0) {
				int xt = *hi;
				s.emplace(xt, y);
				cost[xt][y] = 1 + cost[x][y];
				row[xt].erase(y);
				++hi;
			}
			
			col[y].erase(lo, hi);
		}

		swap(s, q);
	}

	cout << cost[x2][y2] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
