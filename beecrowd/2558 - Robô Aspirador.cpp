#include <bits/stdc++.h>

using namespace std;

using coordenada = tuple<int, int, int>;
using ii = pair<int, int>;

int main() {

	int n, m;
	int count_bits[256];
	
	count_bits[0] = 0;
	
	for(int k = 1; k < 256; ++k)
		count_bits[k] = count_bits[k / 2] + (k & 1);
	
	while(scanf("%d%d", &n, &m) != EOF) {
	
		int w, h, ESTADOS = 1 << n, x, y, xf, yf, ***cst;
		char **mapa;
		map<ii, int> graos;
		
		scanf("%d%d", &w, &h);
		
		mapa = new char*[h];
		cst = new int**[h];
		
		for(int i = 0; i < h; ++i) {
		
			cst[i] = new int*[w];
			
			mapa[i] = new char[w + 1];
			
			scanf("%s", mapa[i]);
			
			for(int j = 0; j < w; ++j) {
			
				if(mapa[i][j] == 'R')
					x = i, y = j;
					
				else if(mapa[i][j] == 'S')
					xf = i, yf = j;
					
				else if(mapa[i][j] == '*') {
				
					int pos = graos.size();
					
					graos[{i, j}] = pos;
				}
				
				cst[i][j] = new int[ESTADOS];
				memset(cst[i][j], -1, ESTADOS * sizeof(int));
			}
		}
		
		queue<coordenada> Q;
		
		cst[x][y][0] = 0;
		
		Q.push(coordenada {x, y, 0});
		
		while(!Q.empty()) {
		
			auto [x, y, e] = Q.front();
	
			Q.pop();
		
			if(cst[x][y][e] < m) {
			
				if(x < h - 1) {
				
					if(int ge = 0; mapa[x + 1][y] == '*' && cst[x + 1][y][(ge = e | 1 << graos[{x + 1, y}])] == -1) {
					
						cst[x + 1][y][ge] = 1 + cst[x][y][e];
						Q.push(coordenada {x + 1, y, ge});
					}
					
					else if(mapa[x + 1][y] != '#') {
					
						if(cst[x + 1][y][e] == -1) {
						
							cst[x + 1][y][e] = 1 + cst[x][y][e];
							Q.push(coordenada {x + 1, y, e});	
						}
					}
				}
				
				if(x) {
				
					if(int ge = 0; mapa[x - 1][y] == '*' && cst[x - 1][y][(ge = e | 1 << graos[{x - 1, y}])] == -1) {
					
						cst[x - 1][y][ge] = 1 + cst[x][y][e];
						Q.push(coordenada {x - 1, y, ge});
					}
					
					else if(mapa[x - 1][y] != '#') {
					
						if(cst[x - 1][y][e] == -1) {
						
							cst[x - 1][y][e] = 1 + cst[x][y][e];
							Q.push(coordenada {x - 1, y, e});	
						}
					}
				}
				
				if(y < w - 1) {
				
					if(int ge = 0; mapa[x][y + 1] == '*' && cst[x][y + 1][(ge = e | 1 << graos[{x, y + 1}])] == -1) {
					
						cst[x][y + 1][ge] = 1 + cst[x][y][e];
						Q.push(coordenada {x, y + 1, ge});
					}
					
					else if(mapa[x][y + 1] != '#') {
					
						if(cst[x][y + 1][e] == -1) {
						
							cst[x][y + 1][e] = 1 + cst[x][y][e];
							Q.push(coordenada {x, y + 1, e});	
						}
					}
				}
				
				if(y) {
				
					if(int ge = 0; mapa[x][y - 1] == '*' && cst[x][y - 1][(ge = e | 1 << graos[{x, y - 1}])] == -1) {
					
						cst[x][y - 1][ge] = 1 + cst[x][y][e];
						Q.push(coordenada {x, y - 1, ge});
					}
					
					else if(mapa[x][y - 1] != '#') {
					
						if(cst[x][y - 1][e] == -1) {
						
							cst[x][y - 1][e] = 1 + cst[x][y][e];
							Q.push(coordenada {x, y - 1, e});	
						}
					}
				}
			}
		}

		int max_rec = -1;
				
		for(int e = 0; e < ESTADOS; ++e) {
	
			if(cst[xf][yf][e] != -1)
				max_rec = max(max_rec, count_bits[e]);
		}
	
		printf("%d\n", max_rec);
			
		for(int i = 0; i < h; ++i) {
		
			for(int j = 0; j < w; ++j)
				delete[] cst[i][j];
				
			delete[] cst[i];
			delete[] mapa[i];
		}
		
		delete[] cst;
		delete[] mapa;
	}
	
	return 0;
}