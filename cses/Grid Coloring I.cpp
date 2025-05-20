#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
 
	cin >> n >> m;
 
	vector<string> grid(n);
 
	for(auto& line : grid) 
		cin >> line;
 
	auto new_grid = grid;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if((i + j) % 2 == 0)
				new_grid[i][j] = grid[i][j] == 'A' ? 'B' : 'A';
			else
				new_grid[i][j] = grid[i][j] == 'C' ? 'D' : 'C';
		}
	}
 
	for(auto& line : new_grid)
		cout << line << '\n';
 
	return 0;
}