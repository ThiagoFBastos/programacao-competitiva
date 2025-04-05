#include <bits/stdc++.h>

using namespace std;

struct point {

	int x0, x1;
	int y0, y1;
	int z0, z1;
};

int main() {
	
	int tests;
	
	scanf("%d", &tests);
	
	for(int i = 1; i <= tests; ++i) {
	
		char **grid;
		int ***state, n, N, x0, x1, y0, y1, z0, z1, target[3][2], h = 0;
		
		scanf("%d", &n);
		
		N = n * n;
		
		grid = new char*[n];
		state = new int**[N];
		
		for(int i = 0; i < n; ++i) {
		
			grid[i] = new char[n + 1];
			
			scanf("%s", grid[i]);
			
			for(int j = 0; j < n; ++j) {
				
				switch(grid[i][j]) {
				
					case 'A': x0 = i, x1 = j; break;
					case 'B': y0 = i, y1 = j; break;
					case 'C': z0 = i, z1 = j; break;
					case 'X':
					
						target[h][0] = i;
						target[h++][1] = j;
				}
			}
		}
		
		for(int i = 0; i < N; ++i) {
		
			state[i] = new int*[N];
			
			for(int j = 0; j < N; ++j) {
			
				state[i][j] = new int[N];
				memset(state[i][j], -1, N * sizeof(int));
			}
		}
		
		queue<point> Q;
		
		state[x0 * n + x1][y0 * n + y1][z0 * n + z1] = 0;
		
		Q.push({x0, x1, y0, y1, z0, z1});
		
		while(!Q.empty()) {
		
			auto [x0, x1, y0, y1, z0, z1] = Q.front();
			
			Q.pop();
			
			{
				int x = x0, y = y0, z = z0;
				
				if(x0 < n - 1 && grid[x0 + 1][x1] != '#') ++x;
				if(y0 < n - 1 && grid[y0 + 1][y1] != '#') ++y;
				if(z0 < n - 1 && grid[z0 + 1][z1] != '#') ++z;
				
				for(int k = 0; k < 2; ++k) {
				
					if(x == z && x1 == z1) {
					
						if(x0 < z0) x = x0;
						else z = z0;
					}
					
					if(x == y && x1 == y1) {
					
						if(x0 < y0) x = x0;
						else z = y0;
					}
					
					if(y == z && y1 == z1) {
					
						if(y0 < z0) y = y0;
						else z = z0;
					}
				}
				
				if(state[x * n + x1][y * n + y1][z * n + z1] == -1) {
				
					state[x * n + x1][y * n + y1][z * n + z1] = 1 + state[x0 * n + x1][y0 * n + y1][z0 * n + z1];
					Q.push({x, x1, y, y1, z, z1});
				}
			}
			
			{
				int x = x0, y = y0, z = z0;
				
				if(x0 && grid[x0 - 1][x1] != '#') --x;
				if(y0 && grid[y0 - 1][y1] != '#') --y;
				if(z0 && grid[z0 - 1][z1] != '#') --z;
				
				for(int k = 0; k < 2; ++k) {
				
					if(x == z && x1 == z1) {
					
						if(x0 > z0) x = x0;
						else z = z0;
					}
					
					if(x == y && x1 == y1) {
					
						if(x0 > y0) x = x0;
						else z = y0;
					}
					
					if(y == z && y1 == z1) {
					
						if(y0 > z0) y = y0;
						else z = z0; 
					}
				}
				
				if(state[x * n + x1][y * n + y1][z * n + z1] == -1) {
				
					state[x * n + x1][y * n + y1][z * n + z1] = 1 + state[x0 * n + x1][y0 * n + y1][z0 * n + z1];
					Q.push({x, x1, y, y1, z, z1});
				}
			}
			
			{
				int x = x1, y = y1, z = z1;
				
				if(x1 < n - 1 && grid[x0][x1 + 1] != '#') ++x;
				if(y1 < n - 1 && grid[y0][y1 + 1] != '#') ++y;
				if(z1 < n - 1 && grid[z0][z1 + 1] != '#') ++z;
			
				for(int k = 0; k < 2; ++k) {
					
					if(x == z && x0 == z0) {
						
						if(x1 < z1) x = x1;
						else z = z1;
					}
						
					if(x == y && x0 == y0) {
						
						if(x1 < y1) x = x1;
						else z = y1;
					}
						
					if(y == z && y0 == z0) {
						
						if(y1 < z1) y = y1;
						else z = z1;
					}
				}
				
				if(state[x0 * n + x][y0 * n + y][z0 * n + z] == -1) {
				
					state[x0 * n + x][y0 * n + y][z0 * n + z] = 1 + state[x0 * n + x1][y0 * n + y1][z0 * n + z1];
					Q.push({x0, x, y0, y, z0, z});
				}	
			}
			
			{
				int x = x1, y = y1, z = z1;
				
				if(x1 && grid[x0][x1 - 1] != '#') --x;
				if(y1 && grid[y0][y1 - 1] != '#') --y;
				if(z1 && grid[z0][z1 - 1] != '#') --z;
				
				for(int k = 0; k < 2; ++k) {
					
					if(x == z && x0 == z0) {
						
						if(x1 > z1) x = x1;
						else z = z1;
					}
						
					if(x == y && x0 == y0) {
						
						if(x1 > y1) x = x1;
						else z = y1;
					}
						
					if(y == z && y0 == z0) {
						
						if(y1 > z1) y = y1;
						else z = z1;
					}
				}
				
				if(state[x0 * n + x][y0 * n + y][z0 * n + z] == -1) {
				
					state[x0 * n + x][y0 * n + y][z0 * n + z] = 1 + state[x0 * n + x1][y0 * n + y1][z0 * n + z1];
					Q.push({x0, x, y0, y, z0, z});
				}
			}
		}
		
		x0 = target[0][0];
		x1 = target[0][1];
		
		y0 = target[1][0];
		y1 = target[1][1];
		
		z0 = target[2][0];
		z1 = target[2][1];
		
		int min_cst = INT_MAX;
		
		if(state[x0 * n + x1][y0 * n + y1][z0 * n + z1] != -1) min_cst = state[x0 * n + x1][y0 * n + y1][z0 * n + z1];
		if(state[x0 * n + x1][z0 * n + z1][y0 * n + y1] != -1) min_cst = min(min_cst, state[x0 * n + x1][z0 * n + z1][y0 * n + y1]);
		if(state[y0 * n + y1][z0 * n + z1][x0 * n + x1] != -1) min_cst = min(min_cst, state[y0 * n + y1][z0 * n + z1][x0 * n + x1]);
		if(state[y0 * n + y1][x0 * n + x1][z0 * n + z1] != -1) min_cst = min(min_cst, state[y0 * n + y1][x0 * n + x1][z0 * n + z1]);
		if(state[z0 * n + z1][x0 * n + x1][y0 * n + y1] != -1) min_cst = min(min_cst, state[z0 * n + z1][x0 * n + x1][y0 * n + y1]);
		if(state[z0 * n + z1][y0 * n + y1][x0 * n + x1] != -1) min_cst = min(min_cst, state[z0 * n + z1][y0 * n + y1][x0 * n + x1]);
		
		printf("Case %d: ", i);
		
		if(min_cst == INT_MAX)
			puts("trapped");
		else
			printf("%d\n", min_cst);
			
		for(int i = 0; i < n; ++i) 
			delete[] grid[i];
		
		for(int i = 0; i < N; ++i) {
		
			for(int j = 0; j < N; ++j)
				delete[] state[i][j];
				
			delete[] state[i];
		}
		
		delete[] grid;
		delete[] state;
	}
	
	return 0;
}