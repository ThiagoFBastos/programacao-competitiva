#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;

int main() {

	int n, m, src, dest;
	
	scanf("%d%d%d%d", &n, &src, &dest, &m);
	
	int **tempo = new int*[n];
	vector<ii> *N = new vector<ii>[n];

	for(int i = 0; i < n; ++i) {
	
		tempo[i] = new int[3];
		tempo[i][0] = tempo[i][1] = tempo[i][2] = -1;
	}
	
	for(int k = 0; k < m; ++k) {
	
		int u, v, t;
		
		scanf("%d%d%d", &u, &v, &t);
		
		N[u].push_back({v, t});
	}
	
	queue<ii> Q;
	
	Q.push({src, 0});
	
	tempo[src][0] = 0;
	
	while(!Q.empty()) {
	
		auto [u, t] = Q.front();
		
		Q.pop();
		
		if(u == dest) 
			break;
		
		for(auto [v, op] : N[u]) {
		
			if(op && t == 0 && tempo[v][1] == -1) {
		
				tempo[v][1] = 1 + tempo[u][t];
				
				Q.push({v, 1});
			}
			
			else if(!op && t && tempo[v][(t + 1) % 3] == -1) {
			
				tempo[v][(t + 1) % 3] = 1 + tempo[u][t];
				Q.push({v, (t + 1) % 3});
			}
		}
	}

	int t = INT_MAX;
	
	if(tempo[dest][0] >= 0) t = min(t, tempo[dest][0]);
	if(tempo[dest][1] >= 0) t = min(t, tempo[dest][1]);
	if(tempo[dest][2] >= 0) t = min(t, tempo[dest][2]);
	
	if(t == INT_MAX) puts("*");
	else printf("%d\n", t);
		
	return 0;
}