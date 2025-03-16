#include "bits/stdc++.h"
using namespace std;
using ii = pair<int, int>;
void solve() {
	int c, n, a, swaps = 0;
	cin >> c >> n >> a;
	vector<int> p(a), lo(n, 0);
	vector<vector<int>> pos(n);
	set<ii, greater<ii>> pq;
	vector<bool> no_set(n, false);
	for(int i = 0; i < a; ++i) {
		cin >> p[i];
		pos[p[i]].push_back(i);
	}
	for(int i = 0; i < n; ++i) pos[i].push_back(a);
	for(int x : p) {
		if(no_set[x]) {
			--swaps;
			pq.erase(make_pair(pos[x][++lo[x]], x));
		} else if(size(pq) == c) {
			int v = pq.begin()->second;
			no_set[v] = false;
			++lo[v];
			pq.erase(pq.begin());
		}
		++swaps;
		pq.insert(make_pair(pos[x][lo[x] + 1], x));
		no_set[x] = true;
	}
	cout << swaps << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}