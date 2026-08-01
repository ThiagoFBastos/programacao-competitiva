#include <bits/stdc++.h>

using namespace std;

constexpr int N = 4e2 + 5;

bool vis[N][N];
char grid[N][N];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int n, m;

	pair<int, int> delta[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	cin >> n >> m;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> grid[i][j];

	int max_connected_component {};

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(vis[i][j] || grid[i][j] != 'C')
				continue;

			queue<pair<int, int>> q;
			int count {};

			vis[i][j] = true;
			q.emplace(i, j);

			while(!q.empty()) {
				auto [x, y] = q.front();

				q.pop();

				++count;

				for(auto [dx, dy] : delta) {
					int x_dest = x + dx, y_dest = y + dy;

					if(x_dest < 0 || y_dest < 0 || x_dest >= n || y_dest >= m || grid[x_dest][y_dest] != 'C' || vis[x_dest][y_dest])
						continue;

					vis[x_dest][y_dest] = true;
					q.emplace(x_dest, y_dest);
				}
			}

			max_connected_component = max(max_connected_component, count);
		}
	}

	cout << max_connected_component << '\n';

	return 0;
}
 