#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e3 + 10, INF = 1e9;
 
int dist[N][N];
pair<int, int> delta[] = {
	{1, 2},
	{1, -2},
	{-1, 2},
	{-1, -2},
	{2, 1},
	{2, -1},
	{-2, 1},
	{-2, -1}
};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	queue<pair<int, int>> q;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			dist[i][j] = -1;
 
	dist[0][0] = 0;
 
	q.emplace(0, 0);
 
	while(!q.empty()) {
		auto [x, y] = q.front();
 
		q.pop();
		
		for(auto [dx, dy] : delta) {
			int tx = x + dx, ty = y + dy;
			
			if(tx < 0 || tx >= n || ty < 0 || ty >= n || dist[tx][ty] != -1) continue;
 
			dist[tx][ty] = 1 + dist[x][y];
			q.emplace(tx, ty);
		}
	}
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			cout << dist[i][j] << ' ';
		cout << '\n';
	}
 
	return 0;
}