#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

vi *N;
int *pai, *low, *entrada, tempo;

bool dfs(int v) {

	low[v] = entrada[v] = ++tempo;

	for(int w : N[v]) {
	
		if(pai[w] == -1) {
		
			pai[w] = v;
			
			if(!dfs(w) || entrada[v] < low[w])
				return false;
			
			low[v] = min(low[v], low[w]);
		}
		
		else if(pai[v] != w) low[v] = min(low[v], entrada[w]);
	}
	
	return true;
}

int main() {

	int n, m;
	
	while(true) {
	
		scanf("%d%d", &n, &m);
	
		if(!(n || m)) break;
		
		N = new vi[n];
		entrada = new int[n];
		low = new int[n];
		pai = new int[n];
		
		memset(pai, -1, n * sizeof(int));
		
		for(int i = 0; i < m; ++i) {
		
			int u, v;
			
			scanf("%d%d", &u, &v);
			
			--u;
			--v;
			
			N[u].push_back(v);
			N[v].push_back(u);
		}
		
		pai[0] = tempo = 0;
		
		if(dfs(0)) puts("S");
		else puts("N");
		
		delete[] N;
		delete[] entrada;
		delete[] low;
		delete[] pai;
	}	
	
	puts("");
	
	return 0;
}