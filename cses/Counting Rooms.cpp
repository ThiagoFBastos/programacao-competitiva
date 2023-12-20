#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
char **grid;
int cc = 0;
void flood_fill(int x, int y) {
	grid[x][y] = '\0';
	if(grid[x - 1][y] == '.') flood_fill(x - 1, y);
	if(grid[x + 1][y] == '.') flood_fill(x + 1, y);
	if(grid[x][y - 1] == '.') flood_fill(x, y - 1);
	if(grid[x][y + 1] == '.') flood_fill(x, y + 1);
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	grid = new char*[n + 2];
	for(int i = 0; i <= n + 1; ++i) {
		grid[i] = new char[m + 2];
		memset(grid[i], '\0', m + 2);
	}
	for(int i = 1; i <= n; ++i)
		scanf("%s", &grid[i][1]);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(grid[i][j] == '.') {
				++cc;
				flood_fill(i, j);
			}
		}
	}
	printf("%d\n", cc);
    return 0;
}
