#include "game.h"
#include <utility>
 
using namespace std;
 
static const int N = 1600;
 
static int edges[N][N];
static int par[N];
static int depth[N];
static int n;
 
static int findSet(int u) {
	return par[u] == u ? u : par[u] = findSet(par[u]);
}
 
static void join(int a, int b) {
	a = findSet(a);
	b = findSet(b);
 
	if(depth[a] > depth[b]) swap(a, b);
 
	edges[a][b] = edges[b][a] = 0;
 
	par[a] = b;
	depth[b] += depth[a] == depth[b];
 
	for(int i = 0; i < n; ++i) {
		int x = edges[a][i];
		edges[a][i] = edges[i][a] = 0;
		edges[b][i] += x;
		edges[i][b] += x;
	}
}
 
void initialize(int n) {
	:: n = n;
	for(int i = 0; i < n; ++i) {
		par[i] = i;
		for(int j = 0; j < n; ++j)
			edges[i][j] = i != j;
	}
}
 
int hasEdge(int u, int v) {
	u = findSet(u);
	v = findSet(v);
	--edges[u][v], --edges[v][u];
	if(edges[u][v] == 0) {
		join(u, v);
		return 1;
	}
	return 0;		
}
