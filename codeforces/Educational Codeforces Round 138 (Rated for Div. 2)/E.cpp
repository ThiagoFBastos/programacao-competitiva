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

const int N = 2e5 + 100;

string g[N];
int cost[2 * N], par[2 * N];

bool valid(int x, int y, int n, int m) {
	for(int dx = -1; dx <= 1; ++dx) {
		for(int dy = -1; dy <= 1; ++dy) {
			if(abs(dx) + abs(dy) != 1) continue;
			int x0 = x + dx, y0 = y + dy;
			if(x0 < 0 || y0 < 0 || x0 >= n || y0 >= m) continue;
			if(g[x0][y0] == '#') return false;
		}
	}
	return true;
}

void solve() {
	int n, m;

	cin >> n >> m;

	for(int i = 0; i < n; ++i) {
		cin >> g[i];
		for(int j = 0; j < m; ++j) {
			par[i * m + j] = -1;
			cost[i * m + j] = INF;
		}
	}
	
	priority_queue<tuple<int, int, int, int>> pq;

	for(int i = 0; i < n; ++i) {
		if(!valid(i, 0, n, m)) continue;
		pq.emplace(-(g[i][0] != '#'), i, 0, i * m);
	}

	while(!pq.empty()) {
		auto [c, x, y, p] = pq.top(); pq.pop();

		if(par[x * m + y] != -1) continue;

		c *= -1;

		par[x * m + y] = p;

		if(y == m - 1) {
			int u = x * m + y;
			cout << "YES\n";
			for(; y; u = par[u]) {
				x = u / m;
				y = u % m;
				g[x][y] = '#';
			}
			for(int i = 0; i < n; ++i) cout << g[i] << '\n';
			return;
		}

		for(int dx : {-1, 1}) {
			for(int dy : {-1, 1}) {
				int x0 = x + dx, y0 = y + dy;
				if(x0 < 0 || y0 < 0 || x0 >= n || y0 >= m || !valid(x0, y0, n, m)) continue;
				int C = c + (g[x0][y0] != '#');
				if(cost[x0 * m + y0] <= C) continue;
				cost[x0 * m + y0] = C;
				pq.emplace(-C, x0, y0, x * m + y);
			}
		}
	}

	cout << "NO\n";	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
