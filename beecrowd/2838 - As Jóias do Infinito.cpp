#include <bits/stdc++.h>

using namespace std;

#define ESTADOS 512

struct step {

	int x0, y0, state, cost;
};

bool operator<(step a, step b) {

	return a.cost > b.cost; 
}

int main() {
	
	int n, m, ***custo, x0, y0;
	char **lab;
	priority_queue<step> pq;

	scanf("%d%d", &n, &m);
	
	lab = new char*[n];
	custo = new int**[n];
	
	for(int i = 0; i < n; ++i) {
	
		lab[i] = new char[m + 1];
		custo[i] = new int*[m];
		
		scanf("%s", lab[i]);
		
		for(int j = 0; j < m; ++j) {
		
			custo[i][j] = new int[ESTADOS];
	
			memset(custo[i][j], -1, ESTADOS * sizeof(int));
			
			if(lab[i][j] == 'T') x0 = i, y0 = j;
		}
	}
	
	pq.push({x0, y0, 0, 0});
	
	while(!pq.empty()) {
	
		int x0, y0, state, cost;
		
		x0 = pq.top().x0;
		y0 = pq.top().y0;
		state = pq.top().state;
		cost = pq.top().cost;
		
		pq.pop();
		
		if(custo[x0][y0][state] == -1) {
		
			custo[x0][y0][state] = cost;
			
			if(x0 < n - 1 && lab[x0 + 1][y0] != '#') {
			
				switch(lab[x0 + 1][y0]) {
				
					int e;
					
					case 'A'...'D':
					
						e = 1 << lab[x0 + 1][y0] - 'A'; 	
						
						if((state & e) && custo[x0 + 1][y0][state] == -1)
							pq.push({x0 + 1, y0, state, 1 + cost});
							
						break;
						
					case 'a'...'d':
					
						e = 1 << lab[x0 + 1][y0] - 'a' | state;
							
						if(custo[x0 + 1][y0][e] == -1)
							pq.push({x0 + 1, y0, e, 1 + cost});
							
						break;
						
					case 'r':

						if(custo[x0 + 1][y0][state | 16] == -1)
							pq.push({x0 + 1, y0, state | 16, 1 + cost});
								
					break;
										
					case 'p':
					
						if(custo[x0 + 1][y0][state | 32] == -1)
							pq.push({x0 + 1, y0, state | 32, 1 + cost});
							
					break;
					
					case 't':
					
						if(custo[x0 + 1][y0][state | 64] == -1)
							pq.push({x0 + 1, y0, state | 64, 1 + cost});
							
					break;
					
					case 'm':
					
						if(custo[x0 + 1][y0][state | 128] == -1)
							pq.push({x0 + 1, y0, state | 128, 1 + cost});
							
					break;
					
					case 'e':
						if(custo[x0 + 1][y0][state | 256] == -1)
							pq.push({x0 + 1, y0, state | 256, 1 + cost});
							
					break;
					
					default:
					
						if(custo[x0 + 1][y0][state] == -1)
							pq.push({x0 + 1, y0, state, 1 + cost});
				}
			}
			
			if(x0 && lab[x0 - 1][y0] != '#') {
			
				switch(lab[x0 - 1][y0]) {
				
					int e;
					
					case 'A'...'D':
					
						e = 1 << lab[x0 - 1][y0] - 'A'; 	
						
						if((state & e) && custo[x0 - 1][y0][state] == -1)
							pq.push({x0 - 1, y0, state, 1 + cost});
							
						break;
						
					case 'a'...'d':
					
						e = 1 << lab[x0 - 1][y0] - 'a' | state;
						
						if(custo[x0 - 1][y0][e] == -1)
							pq.push({x0 - 1, y0, e, 1 + cost});
							
						break;
					
					case 'r':

						if(custo[x0 - 1][y0][state | 16] == -1)
							pq.push({x0 - 1, y0, state | 16, 1 + cost});
								
					break;
										
					case 'p':
					
						if(custo[x0 - 1][y0][state | 32] == -1)
							pq.push({x0 - 1, y0, state | 32, 1 + cost});
							
					break;
					
					case 't':
					
						if(custo[x0 - 1][y0][state | 64] == -1)
							pq.push({x0 - 1, y0, state | 64, 1 + cost});
							
					break;
					
					case 'm':
					
						if(custo[x0 - 1][y0][state | 128] == -1)
							pq.push({x0 - 1, y0, state | 128, 1 + cost});
							
					break;
					
					case 'e':
						if(custo[x0 - 1][y0][state | 256] == -1)
							pq.push({x0 - 1, y0, state | 256, 1 + cost});
							
					break;
					
					default:
					
						if(custo[x0 - 1][y0][state] == -1)
							pq.push({x0 - 1, y0, state, 1 + cost});
				}
			}
			
			if(y0 < m - 1 && lab[x0][y0 + 1] != '#') {
			
				switch(lab[x0][y0 + 1]) {
				
					int e;
					
					case 'A'...'D':
					
						e = 1 << lab[x0][y0 + 1] - 'A'; 	
						
						if((state & e) && custo[x0][1 + y0][state] == -1)
							pq.push({x0, 1 + y0, state, 1 + cost});
							
						break;
						
					case 'a'...'d':
					
						e = 1 << lab[x0][y0 + 1] - 'a' | state;
						
						if(custo[x0][1 + y0][e] == -1)
							pq.push({x0, 1 + y0, e, 1 + cost});
							
						break;
						
					case 'r':

						if(custo[x0][y0 + 1][state | 16] == -1)
							pq.push({x0, y0 + 1, state | 16, 1 + cost});
								
					break;
										
					case 'p':
					
						if(custo[x0][y0 + 1][state | 32] == -1)
							pq.push({x0, y0 + 1, state | 32, 1 + cost});
							
					break;
					
					case 't':
					
						if(custo[x0][y0 + 1][state | 64] == -1)
							pq.push({x0, y0 + 1, state | 64, 1 + cost});
							
					break;
					
					case 'm':
					
						if(custo[x0][y0 + 1][state | 128] == -1)
							pq.push({x0, y0 + 1, state | 128, 1 + cost});
							
					break;
					
					case 'e':
						if(custo[x0][y0 + 1][state | 256] == -1)
							pq.push({x0, y0 + 1, state | 256, 1 + cost});
							
					break;
					
					default:
					
						if(custo[x0][y0 + 1][state] == -1)
							pq.push({x0, y0 + 1, state, 1 + cost});
				}
			}
			
			if(y0 && lab[x0][y0 - 1] != '#') {
			
				switch(lab[x0][y0 - 1]) {
				
					int e;
					
					case 'A'...'D':
					
						e = 1 << lab[x0][y0 - 1] - 'A'; 	
						
						if((state & e) && custo[x0][y0 - 1][state] == -1)
							pq.push({x0, y0 - 1, state, 1 + cost});
							
						break;
						
					case 'a'...'d':
					
						e = 1 << lab[x0][y0 - 1] - 'a' | state;
						
						if(custo[x0][-1 + y0][e] == -1)
							pq.push({x0, -1 + y0, e, 1 + cost});
							
						break;
						
					case 'r':

						if(custo[x0][y0 - 1][state | 16] == -1)
							pq.push({x0, y0 - 1, state | 16, 1 + cost});
								
					break;
					
					case 'p':
					
						if(custo[x0][y0 - 1][state | 32] == -1)
							pq.push({x0, y0 - 1, state | 32, 1 + cost});
							
					break;
					
					case 't':
					
						if(custo[x0][y0 - 1][state | 64] == -1)
							pq.push({x0, y0 - 1, state | 64, 1 + cost});
							
					break;
					
					case 'm':
					
						if(custo[x0][y0 - 1][state | 128] == -1)
							pq.push({x0, y0 - 1, state | 128, 1 + cost});
							
					break;
					
					case 'e':
						if(custo[x0][y0 - 1][state | 256] == -1)
							pq.push({x0, y0 - 1, state | 256, 1 + cost});
							
					break;
					
					default:
					
						if(custo[x0][y0 - 1][state] == -1)
							pq.push({x0, y0 - 1, state, 1 + cost});
				}
			}
		}
	}		
	
	int mintime = numeric_limits<int> :: max();
	
	for(int i = 0; i < n; ++i) {
	
		for(int j = 0; j < m; ++j) {
		
			if(lab[i][j] == 'p' || lab[i][j] == 't' || lab[i][j] == 'm' || lab[i][j] == 'e' || lab[i][j] == 'r') {
			
				for(int k = 496; k < 512; ++k)
					if(custo[i][j][k] != -1)
						mintime = min(mintime, custo[i][j][k]);
			}	
		}
	}
	
	if(mintime == numeric_limits<int> :: max())
		puts("Gamora");
	else
		printf("%d\n", mintime);
	
	return 0;
}