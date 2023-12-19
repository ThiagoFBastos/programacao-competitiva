#include <bits/stdc++.h>
using namespace std;
int n, q, **bit;
void update(int x, int y, int v) {
	while(x <= n) {
		for(int z = y; z <= n; z += z & -z)
			bit[x][z] += v;
		x += x & -x;
	}
}
int query(int x, int y) {
	int res = 0;
	while(x > 0) {
		for(int z = y; z > 0; z -= z & -z)
			res += bit[x][z];
		x -= x & -x;
	}
	return res;
}
int query(int x0, int y0, int x1, int y1) {
	return query(x1, y1) - query(x1, y0 - 1) - query(x0 - 1, y1) + query(x0 - 1, y0 - 1);	
}
int main() {
	char **grid;
	scanf("%d%d", &n, &q);
	grid = new char*[n];
	bit = new int*[n + 1];
	for(int i = 0; i <= n; ++i) {
		bit[i] = new int[n + 1];
		memset(bit[i], 0, (n + 1) * sizeof(int));
	}
	for(int i = 0; i < n; ++i) {
		grid[i] = new char[n + 1];
		scanf("%s", grid[i]);
		for(int k = 0; k < n; ++k) {
			if(grid[i][k] == '*') 
				update(i + 1, k + 1, 1);
		}
	}
	while(q--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int x, y;
			scanf("%d%d", &x, &y);
			if(grid[x - 1][y - 1] == '*') {
				grid[x - 1][y - 1] = '.';
			 	update(x, y, -1);
			}
			else {
				grid[x - 1][y - 1] = '*'; 
				update(x, y, 1);
			}
		}
		else {
			int x0, y0, x1, y1;
			scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
			printf("%d\n", query(x0, y0, x1, y1));			
		}
	}
	return 0;
}
