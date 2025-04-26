#include "bits/stdc++.h"

using namespace std;

const int N = 1e2, inf = 1e9 + 1;

int topo(vector<vector<int>>& g) {
	int n = size(g), m = size(g[0]), ans = 0;
	
	auto vis = vector<vector<bool>>(n, vector<bool>(m, false));
	
	for(int i = 1; i < n - 1; ++i) {
		for(int j = 1; j < m - 1; ++j) {
			if(vis[i][j]) continue;
			queue<pair<int, int>> q;
			vis[i][j] = true;
			q.push({i, j});
			++ans;
			while(!q.empty()) {
				auto [x, y] = q.front();
				q.pop();
				for(int a = -1; a <= 1; ++a) {
					for(int b = -1; b <= 1; ++b) {
						if(abs(a) + abs(b) != 1 || vis[x + a][y + b] || g[x + a][y + b] != g[x][y]) continue;
						vis[x + a][y + b] = true;
						q.push({x + a, y + b});
					}
				}
			}
		}
	}
	
	return ans;
}

int faces(vector<vector<int>>& g) {
	int n = size(g), m = size(g[0]), ans = 0;
	
	for(int i = 1; i < n - 1; ++i) {
		int l = inf, r = -inf;
		for(int j = 1; j < m - 1; ++j) {
			if(g[i][j] > g[i + 1][j]) {
				int L = g[i + 1][j] + 1, R = g[i][j];
				ans += max(l, L) > min(r, R);
				l = L, r = R;
			} else l = inf, r = -inf;
		}
	}
	
	return ans;
}

auto rotate(vector<vector<int>>& g) {
	int n = size(g), m = size(g[0]);
	auto _g = vector<vector<int>>(m, vector<int>(n));
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
		_g[m - j - 1][i] = g[i][j];
	return _g;
}

void solve() {
	int n, m, f = 5;
	
	cin >> n >> m;
	
	auto g = vector<vector<int>>(n + 2, vector<int>(m + 2, inf));
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		cin >> g[i][j];
	
	f += topo(g);
	
	for(int i = 0; i < 4; ++i) {
		f += faces(g);
		g = rotate(g);
	}
	
	cout << f << '\n';
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}