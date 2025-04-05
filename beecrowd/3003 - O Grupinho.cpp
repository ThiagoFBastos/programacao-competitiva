#include <bits/stdc++.h>

using namespace std;

static vector<int> *N;
static int w, X, Y;
static bool *seen;

static void dfs(int);

void dfs(int v) {

	seen[v] = false;
	++w;
	
	if(N[v].size() == 1) ++X;
	else if(N[v].size() == 2) ++Y;
	
	for(int u : N[v]) {
	
		if(seen[u])
			dfs(u);
	}
}

int main() {

	int n, m;
	
	scanf("%d%d", &n, &m);
	
	N = new vector<int>[n];
	seen = new bool[n];
	
	for(int v = 0; v < n; ++v)
		seen[v] = true;
		
	for(int i = 0; i < m; ++i) {
	
		int u, v;
		
		scanf("%d%d", &u, &v);
		
		--u;
		--v;
		
		N[u].push_back(v);
		N[v].push_back(u);
	}
	
	bool sat = false;
	int Z = 0;
	
	for(int v = 0; v < n; ++v) {
	
		if(seen[v]) {
		
			w = X = Y = 0;
			
			dfs(v);
			
			if(w == 1)
				++Z;
				
			else if(w < 6 && !(w == 3 && Y == w) && X + Y == w && (Y == w || X == 2)) {
			
				if(w == 2)
					++Z;
				
				else 
					Z += 2;
			}
			
			else {
			
				sat = true;
				break;
			}
		}
	}
	
	if(sat || Z >= 3) puts("Festa bunita, festa formosa.");
	else puts("Role torto.");
	
	return 0;
}
