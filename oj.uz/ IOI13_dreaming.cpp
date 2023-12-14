#include "dreaming.h"
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
 
using namespace std;
 
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    vector<int> dmax(N, -1), d;
	vector<vector<pair<int, int>>> g(N);
	int y, ans = 0;
 
	for(int i = 0; i < M; ++i) {
		g[A[i]].emplace_back(B[i], T[i]);
		g[B[i]].emplace_back(A[i], T[i]);
	}
 
	function<void(int, int)> preProcess = [&](int u, int p) {
		dmax[u] = 0;
		for(auto [v, w] : g[u]) {
			if(v == p) continue;
			preProcess(v, u);
			dmax[u] = max(dmax[u], dmax[v] + w);
		}
	};
 
	function<void(int, int, int)> dfs = [&](int u, int p, int x) {
		int d[2] = {0};
		for(auto [v, w] : g[u]) {
			if(v == p) continue;
			else if(w + dmax[v] > d[0]) d[1] = d[0], d[0] = w + dmax[v];
			else d[1] = max(d[1], w + dmax[v]);
		}
		dmax[u] = max(dmax[u], x);
		y = min(y, dmax[u]);
		ans = max(ans, dmax[u]);
		for(auto [v, w] : g[u]) {
			if(v == p) continue;
			dfs(v, u, w + max(x, d[w + dmax[v] == d[0]]));
		}
	};
 
	for(int i = 0; i < N; ++i) {
		if(dmax[i] != -1) continue;
		y = numeric_limits<int> :: max();
		preProcess(i, i);
		dfs(i, i, 0);
		d.push_back(y);
	}
 
	sort(d.rbegin(), d.rend());
 
	if(M < N - 1) ans = max(ans, d[0] + d[1] + L);
	if(M < N - 2) ans = max(ans, d[1] + d[2] + 2 * L);
 
	return ans;
}
