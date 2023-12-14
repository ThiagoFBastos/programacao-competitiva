#include "factories.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;
 
const int N = 5e5 + 10;
 
vector<pair<int, int>> adj[N], tour;
long long cost[N];
int tms, depth[N], in[N], pos[N], n;
 
void dfs(int u, int p) {
	in[u] = tms++;
	pos[u] = tour.size();
	tour.emplace_back(depth[u], u);
	for(auto [v, w] : adj[u]) {
		if(v == p) continue;
		cost[v] = cost[u] + w;
		depth[v] = depth[u] + 1;
		dfs(v, u);
		tour.emplace_back(depth[u], u);
	}
}
 
vector<vector<pair<int, int>>> sp;
const long long INF = 1e15L;
 
int lca(int a, int b) {
	if(pos[a] > pos[b]) swap(a, b);
	int lg = 31 - __builtin_clz(pos[b] - pos[a] + 1);
	return min(sp[lg][pos[a]], sp[lg][pos[b] - (1 << lg) + 1]).second;
}
 
void Init(int N, int A[], int B[], int D[]) {
	n = N;
	for(int i = 0; i < N - 1; ++i) {
		adj[A[i]].emplace_back(B[i], D[i]);	
		adj[B[i]].emplace_back(A[i], D[i]);
	}
	dfs(0, 0);
	int lg = 32 - __builtin_clz(tour.size());
	sp = vector<vector<pair<int, int>>>(lg, vector<pair<int, int>>(tour.size()));
	for(int i = 0; i < (int)tour.size(); ++i) sp[0][i] = tour[i];
	for(int i = 1; i < lg; ++i)
	for(int j = 0; j + (1 << i) <= (int)tour.size(); ++j)
		sp[i][j] = min(sp[i - 1][j], sp[i - 1][(1 << (i - 1)) + j]);
}
 
bool cmp(pair<int, int> a, pair<int, int> b) {
	return in[a.first] < in[b.first];
}
 
long long st[2][2 * N];
vector<pair<int, int>> U;
 
long long query(long long st[], int l, int r) {
	long long ans = INF;
	int n = U.size();
	for(l += n, r += n; l <= r; l /= 2, r /= 2) {
		if(l & 1) ans = min(ans, st[l++]);
		if(~r & 1) ans = min(ans, st[r--]);
	}
	return ans;
}
 
long long solve(int lo, int hi, int p) {
	if(lo >= hi) return INF;
	int l = lo, r = hi + 1;
 
	while(l < r) {
		int mid = (l + r) / 2;
		int u = U[lo].first, v = U[mid].first;
		if(lca(u, v) == p) r = mid;
		else l = mid + 1;
	}
 
	if(r <= lo) return solve(lo + 1, hi, p);
	int u = U[lo].first, v = U[r - 1].first;
	int w = lca(u, v);
	long long ans = query(st[0], lo, r - 1) + query(st[1], lo, r - 1) - 2 * cost[w];	
	return min(ans, min(solve(lo, r - 1, w),solve(r, hi, p)));
}
 
long long Query(int S, int X[], int T, int Y[]) {
 
	U.resize(S + T);
	for(int i = 0; i < S; ++i) U[i] = {X[i], 0};
	for(int i = 0; i < T; ++i) U[S + i] = {Y[i], 1};
	sort(U.begin(), U.end(), cmp);
 
	int m = S + T;
 
	for(int i = 0; i < m; ++i) {
		st[0][i + m] = cost[U[i].first];
		st[1][i + m] = INF;
		if(U[i].second) swap(st[0][i + m], st[1][i + m]);	
	}
 
	for(int k = 0; k < 2; ++k)
	for(int i = m - 1; i >= 0; --i)
		st[k][i] = min(st[k][2 * i], st[k][2 * i + 1]);
	
	return solve(0, m - 1, -1);
}
