#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 2500;
 
int dist[N][N][2];
vector<int> adj[N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m, q;	
 
	cin >> n >> m >> q;
 
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
 
	for(int v = 0; v < n; ++v) {
		queue<pair<int, int>> Q;
 
		for(int u = 0; u < n; ++u)
			for(int p = 0; p < 2; ++p)
				dist[v][u][p] = -1;
 
		Q.emplace(v, 0);
		dist[v][v][0] = 0;
 
		while(!Q.empty()) {
			auto [u, p] = Q.front();
			Q.pop();
 
			for(int w : adj[u]) {
				if(dist[v][w][p ^ 1] != -1)
					continue;
					
				dist[v][w][p ^ 1] = 1 + dist[v][u][p];
				Q.emplace(w, p ^ 1);
			}
		}
	}
 
	while(q--) {
		int a, b, x;
 
		cin >> a >> b >> x;
		
		--a, --b;
 
		if(dist[a][b][x & 1] != -1 && dist[a][b][x & 1] <= x)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
 
	return 0;
}
