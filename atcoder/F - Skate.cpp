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

ii delta[] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

void solve() {
	int h, w, n;
	int x0, y0;
	int x1, y1;

	cin >> h >> w >> n;

	cin >> x0 >> y0;
	cin >> x1 >> y1;

	vector<ii> p, q;
	map<int, set<int>> col, row;
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		col[y].insert(x);
		row[x].insert(y);
		for(auto [dx, dy] : delta) {
			int _x = x + dx;
			int _y = y + dy;
			if(_x < 0 || _y < 0 || _x > h || _y > w) continue;			
			q.emplace_back(_x, _y);
		}	
	}

	q.emplace_back(x0, y0);
	sort(q.begin(), q.end());
	q.resize(unique(q.begin(), q.end()) - q.begin());

	if(!binary_search(q.begin(), q.end(), ii(x1, y1))) {
		cout << "-1\n";
		return;
	}

	n = q.size();

	vector<i64> cost(n, -1);
	set<pair<i64, int>> pq;

	pq.insert(make_pair(0LL, int(lower_bound(q.begin(), q.end(), ii(x0, y0)) - q.begin())));

	auto down = [&](ii u) {
		auto [x, y] = u;
		if(!col.count(y)) return -1;
		auto& a = col[y];
		auto it = a.lower_bound(x);
		if(it == a.end()) return -1;
		return int(lower_bound(q.begin(), q.end(), ii(*it - 1, y)) - q.begin());
	};

	auto up = [&](ii u) {
		auto [x, y] = u;
		if(!col.count(y)) return -1;
		auto& a = col[y];
		auto it = a.lower_bound(x);
		if(it == a.begin()) return -1;
		it = prev(it);
		return int(lower_bound(q.begin(), q.end(), ii(*it + 1, y)) - q.begin());
	};

	auto left = [&](ii u) {
		auto [x, y] = u;
		if(!row.count(x)) return -1;
		auto& a = row[x];
		auto it = a.lower_bound(y);
		if(it == a.begin()) return -1;
		it = prev(it);
		return int(lower_bound(q.begin(), q.end(), ii(x, *it + 1)) - q.begin());
	};

	auto right = [&](ii u) {
		auto [x, y] = u;
		if(!row.count(x)) return -1;
		auto& a = row[x];
		auto it = a.lower_bound(y);
		if(it == a.end()) return -1;
		return int(lower_bound(q.begin(), q.end(), ii(x, *it - 1)) - q.begin());
	};

	while(!pq.empty()) {
		auto [c, x] = *pq.begin();
		pq.erase(pq.begin());
		if(cost[x] != -1) continue;
		cost[x] = c;
		int i = down(q[x]);
		if(i != -1 && cost[i] == -1) pq.insert(make_pair(c + 1, i));
		i = up(q[x]);
		if(i != -1 && cost[i] == -1) pq.insert(make_pair(c + 1, i));
		i = right(q[x]);
		if(i != -1 && cost[i] == -1) pq.insert(make_pair(c + 1, i));
		i = left(q[x]);
		if(i != -1 && cost[i] == -1) pq.insert(make_pair(c + 1, i));
	}

	int k = lower_bound(q.begin(), q.end(), ii(x1, y1)) - q.begin();
	cout << cost[k] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

