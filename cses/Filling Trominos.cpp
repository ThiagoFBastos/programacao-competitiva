#include "bits/stdc++.h"
 
using namespace std;
 
const int N = 1e2 + 10;
 
int grid[N][N], tmp[N][N];
char ans[N][N];
int id;
 
void evenColumn(int grid[][N], int x0, int y0, int n, int m) {
	for(int j = 0; j < m; j += 2) {
/*
		A A
		A B
		B B
*/
		for(int i = 0; i < n; i += 3) {
			grid[x0 + i][y0 + j] = grid[x0 + i][y0 + j + 1] = grid[x0 + i + 1][y0 + j] = id++;
			grid[x0 + i + 1][y0 + j + 1] = grid[x0 + i + 2][y0 + j] = grid[x0 + i + 2][y0 + j + 1] = id++;
		}
	}
}
 
void _5x9(int grid[][N], int x0, int y0) {
/*
	1   1  3  4  4 
	1   2  3  3  4
	2   2  6  7  7
	5   6  6  7 10
	5   5  9 10 10
	8   9  9 11 11
	8   8 13 13 11
	15 15 14 13 12
	15 14 14 12 12
*/
 
	int templ[9][5] = {
		{1, 1, 3, 4, 4},
		{1, 2, 3, 3, 4},
		{2, 2, 6, 7, 7},
		{5, 6, 6, 7, 10},
		{5, 5, 9, 10, 10},
		{8, 9, 9, 11, 11},
		{8, 8, 13, 13, 11},
		{15, 15, 14, 13, 12},
		{15, 14, 14, 12, 12}
	};
 
	int cur[16];
 
	for(int i = 1; i <= 15; ++i) cur[i] = id++;
 
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 5; ++j)
			grid[y0 + j][x0 + i] = cur[templ[i][j]];
}
 
bool trominos(int grid[][N], int x0, int y0, int n, int m) {
	int local[N][N];
 
	if(n * m % 3 || min(n, m) == 1 || (n == 3 && m % 2) || (m == 3 && n % 2)) return false;
	else if(n % 3 == 0 && m % 2 == 0) evenColumn(grid, x0, y0, n, m);
	else if(n % 2 == 0 && m % 3 == 0) {
		trominos(local, y0, x0, m, n);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				grid[x0 + i][y0 + j] = local[y0 + j][x0 + i];
	} else if(m % 3) {
		trominos(local, y0, x0, m, n);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				grid[x0 + i][y0 + j] = local[y0 + j][x0 + i];
	} else if(m % 6 == 0) {
		//3 x 6 + (n - 3) x 6
		evenColumn(grid, x0, y0, 3, m);
		trominos(grid, x0 + 3, y0, n - 3, m);
	} else {
		
		_5x9(grid, x0, y0);
		trominos(grid, x0 + 5, y0, n - 5, 9);
		trominos(grid, x0, y0 + 9, n, m - 9);
		
		/*
			5   x 9
						n x m - 9
			n-5 x 9
		*/
	}
 
	return true;
}
 
void label(int grid[][N], char ans[][N], int n, int m) {
	for(int i = 0; i < n; ++i) memset(ans[i], '\0', m + 1);
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(ans[i][j]) continue;
 
			vector<pair<int, int>> group;
 
			for(int dx : {-1, 0, 1}) {
				for(int dy : {-1, 0, 1}) {
					int x = i + dx, y = j + dy;
					if(x < 0 || y < 0 || x >= n || y >= m || grid[x][y] != grid[i][j]) continue;
					group.emplace_back(x, y);
				}
			}
 
			for(char c = 'A'; c <= 'Z'; ++c) {
				bool bad = false;
 
				for(auto [x0, y0] : group) {
					for(int dx : {-1, 0, 1}) {
						for(int dy : {-1, 0, 1}) {
							int x = x0 + dx, y = y0 + dy;
							bad = bad || (x >= 0 && x < n && y >= 0 && y < m && ans[x][y] == c);
						}
					}
				}
	
				if(bad) continue;
 
				for(auto [x0, y0] : group) ans[x0][y0] = c;
 
				break;
			}
		}
	}	
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
 
	int t;
 
	cin >> t;
 
	while(t--) {
		int n, m;
 
		cin >> n >> m;
 
		id = 0;
		if(!trominos(grid, 0, 0, n, m)) {
			cout << "NO\n";
			continue;
		}
 
		label(grid, ans, n, m);
		
		cout << "YES\n";
		for(int i = 0; i < n; ++i) cout << ans[i] << '\n';
	}
 
    return 0;
}
