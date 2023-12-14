#include <bits/stdc++.h>
#include "grader.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int MAXN = 522;
 
vector<int> adj[MAXN];
int walk[MAXN], t;
 
void dfs(int u, int p) {
	walk[t++] = u;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
	}
}
 
int findEgg (int N, vector < pair < int, int > > bridges) {
    t = 0;
 
	for(int i = 0; i < N; ++i) adj[i].clear();
 
	for(auto [u, v] : bridges) {
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
 
	dfs(0, 0);
 
	int l = 0, r = N - 1;
 
	while(l < r) {
		int m = (l + r) / 2;
		vector<int> h;
		for(int i = 0; i <= m; ++i) h.pb(walk[i] + 1);
		if(query(h)) r = m;
		else l = m + 1;
	}
 
	return walk[r] + 1;
}
