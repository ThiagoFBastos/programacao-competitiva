#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;
const int MAXN = 100;
int grid[MAXN][MAXN], n, m, k, pos = 0;
vi G[500];
void dfs(int x, int y) {
	int u, v;	
	u = grid[x][y] = pos++;
	G[u].clear();
	if(x < n - 1) {
		if(grid[x + 1][y] == -1) dfs(x + 1, y);
		if(grid[x + 1][y] >= 0) G[u].push_back(grid[x + 1][y]);
	}
	if(x) {
		if(grid[x - 1][y] == -1) dfs(x - 1, y);
		if(grid[x - 1][y] >= 0) G[u].push_back(grid[x - 1][y]);
	}
	if(y < m - 1) {
		if(grid[x][y + 1] == -1) dfs(x , y + 1);
		if(grid[x][y + 1] >= 0) G[u].push_back(grid[x][y + 1]);
	}
	if(y) {
		if(grid[x][y - 1] == -1) dfs(x, y - 1);
		if(grid[x][y - 1] >= 0) G[u].push_back(grid[x][y - 1]);
	}
}
int matching() {
	int M[500][500], freeV[500], p[500][2];
	for(int u = 0; u < pos; ++u) {
		freeV[u] = 1;
		for(int v = 0; v < pos; ++v)
			M[u][v] = 0;
	}
	while(true) {
		int u {-1};
		queue<ii> S;
		for(int v = 0; v < pos; ++v) {
			p[v][0] = p[v][1] = -1;
			if(freeV[v]) {
				p[v][0] = v;
				S.push({v, 0});
			}
		}
		while(!S.empty()) {
			auto [v, t] = S.front();
			S.pop();
			if(t && freeV[v]) {
				u = v;
				break;
			}
			for(int w : G[v]) {
				if(p[w][1 ^ t] == -1 && M[v][w] == t) {
					p[w][1 ^ t] = v;
					S.push({w, t ^ 1});
				}
			}
		}
		if(u == -1) break;
		for(int i = 1; ; i ^= 1) {
			int v = p[u][i];
			freeV[u] = 0;
			if(u == v) break;
			M[u][v] = M[v][u] = i;
			u = v;
		}
	}
	int emp = 0;
	for(int u = 0; u < pos; ++u)
		for(int v = u + 1; v < pos; ++v)
			emp += M[u][v];
	return emp;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		cin >> n >> m;
		if(!(n || m)) break;
		for(int i = 0; i < n; ++i)
			for(int k = 0; k < m; ++k)
				grid[i][k] = -1;
		cin >> k;
		for(int i = 0; i < k; ++i) {
			int x, y;
			cin >> x >> y;
			grid[x - 1][y - 1] = -2;
		}
		int count = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(grid[i][j] == -1) {
					pos = 0;
					dfs(i, j);
					count += matching();
				}
			}
		}
		cout << count << '\n';
	}
	return 0;
}