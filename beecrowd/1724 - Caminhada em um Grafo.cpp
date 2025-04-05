#include <bits/stdc++.h>

using namespace std;

using point  = tuple<int, int, int>;

int main() {

	int n;
	
	while(true) {
	
		char **grafo;
		int ***custo, x, y, z, mincst = INT_MAX;
	
		scanf("%d", &n);
		
		if(n == 0) 
			break;
			
		scanf("%d%d%d", &x, &y, &z);
		
		grafo = new char*[n];
		custo = new int**[n];
		
		for(int i = 0; i < n; ++i) {
		
			grafo[i] = new char[n];
			custo[i] = new int*[n];
			
			for(int j = 0; j < n; ++j) {
			
				scanf(" %c", &grafo[i][j]);
				
				custo[i][j] = new int[n];
				memset(custo[i][j], -1, n * sizeof(int));
			}
		}
		
		queue<point> Q;
		
		Q.push(point {x - 1, y - 1, z - 1});
		custo[x - 1][y - 1][z - 1] = 0;
		
		while(!Q.empty()) {
		
			auto [x, y, z] = Q.front();
			
			char a, b, c;
			
			if(x == y && y == z) {
			
				mincst = custo[x][y][z];
				break;
			}
				
			Q.pop();
			
			a = grafo[x][y];
			b = grafo[x][z];
			c = grafo[y][z];
			
			for(int v = 0; v < n; ++v) {
			
				if(grafo[x][v] == c && custo[v][y][z] == -1) {
				
					custo[v][y][z] = 1 + custo[x][y][z];	
					Q.push(point {v, y, z});
				}
			}
			
			for(int v = 0; v < n; ++v) {
			
				if(grafo[y][v] == b && custo[x][v][z] == -1) {
			
					custo[x][v][z] = 1 + custo[x][y][z];	
					Q.push(point {x, v, z});
				}
			}
			
			for(int v = 0; v < n; ++v) {
			
				if(grafo[z][v] == a && custo[x][y][v] == -1) {
				
					custo[x][y][v] = 1 + custo[x][y][z];	
					Q.push(point {x, y, v});
				}
			}
		}
		
		if(mincst == INT_MAX) puts("impossible");
		else printf("%d\n", mincst);
		
		for(int i = 0; i < n; ++i) {
		
			for(int j = 0; j < n; ++j) delete[] custo[i][j];
			delete[] grafo[i];
			delete[] custo[i];
		}
		
		delete[] grafo;
		delete[] custo;
	}
	
	return 0;
}