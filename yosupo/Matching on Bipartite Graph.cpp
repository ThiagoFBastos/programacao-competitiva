#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 1e5 + 10, INF = 1e9;

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int n, m, e;

bool bfs() {
	queue<int> q;
	for(int u = 1; u <= m; ++u) {
		if(pairU[u] == 0) {
			dist[u] = 0;
			q.push(u);
		} else dist[u] = INF;
	}
	dist[0] = INF;
	while(!q.empty()) {
		int u = q.front();
		q.pop();		
		if(dist[u] >= dist[0]) continue;
		for(int v : adjU[u]) {
			if(dist[pairV[v]] == INF) {
				dist[pairV[v]] = dist[u] + 1;
				q.push(pairV[v]);
			}
		}
	}
	return dist[0] != INF;
}

bool dfs(int u) {
	if(!u) return true;
	for(int v : adjU[u]) {
		if(dist[pairV[v]] == dist[u] + 1) {
			if(dfs(pairV[v])) {
				pairV[v] = u;
				pairU[u] = v;
				return true;
			}
		}		
	}
	dist[u] = INF;
	return false;
}

int hopcroftKarp() {
	int result = 0;
	while(bfs()) {
		for(int u = 1; u <= m; ++u) {
			if(pairU[u] == 0 && dfs(u)) ++result;
		}
	}
	return result;
}

void solve() {
	cin >> n >> m >> e;
	while(e--) {
		int a, b;
		cin >> a >> b;
		++a, ++b;
		adjU[b].push_back(a);
	}
	cout << hopcroftKarp() << '\n';
	for(int u = 1; u <= m; ++u) {
		if(!pairU[u]) continue;
		cout << pairU[u] - 1 << ' ' << u - 1 << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}