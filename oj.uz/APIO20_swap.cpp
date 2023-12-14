#include "swap.h"
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e5 + 10;
 
int par[MAXN], depth[MAXN], t[MAXN], third[MAXN], deg[MAXN];
 
int findSet(int u) {
	return u == par[u] ? u : findSet(par[u]);
}
 
void merge(int u, int v, int w) {
	int a = findSet(u);
	int b = findSet(v);
	if(depth[a] > depth[b]) swap(a, b);
	++deg[u], ++deg[v];
	if(a == b) third[a] = min(third[a], w);
	else {
		par[a] = b;
		depth[b] += depth[a] == depth[b];
		int x = max(w, third[a]), y = max(w, third[b]);
		if(max(deg[u], deg[v]) > 2) x = min(x, w), y = min(y, w);	
		t[a] = w;
		third[b] = min(third[b], x);
		third[a] = min(third[a], y);
	}
}
 
void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
	for(int i = 0; i < N; ++i) {
		par[i] = i;
		third[i] = INT_MAX;
	}
	vector<tuple<int, int, int>> edge(M);
	for(int i = 0; i < M; ++i) edge[i] = {W[i], U[i], V[i]};
	sort(edge.begin(), edge.end());
	for(auto [w, u, v] : edge) merge(u, v, w);
}
 
int h(int u) {
	return u == par[u] ? 0 : 1 + h(par[u]);
}
 
int getMinimumFuelCapacity(int X, int Y) {
	int hx = h(X), hy = h(Y);
	int ans = 0, trd = INT_MAX;
	while(hx != hy) {
		if(hx < hy) {
			swap(hx, hy);
			swap(X, Y);
		}
		--hx;
		trd = min(trd, third[X]);
		ans = max(ans, t[X]);
		X = par[X];
	}
	while(X != Y) {
		ans = max(ans, max(t[X], t[Y]));
		trd = min(trd, min(third[X], third[Y]));
		X = par[X];
		Y = par[Y];
	}
	trd = min(trd, third[X]);
	while(X != par[X] && trd == INT_MAX) {
		ans = max(ans, t[X]);
		X = par[X];
		trd = min(trd, third[X]);
	}	
	ans = max(ans, trd);
	return ans == INT_MAX ? -1 : ans;
}
