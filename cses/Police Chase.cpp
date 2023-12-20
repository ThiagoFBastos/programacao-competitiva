#include "bits/stdc++.h"
using namespace std;
 
using ii = pair<int, int>;
 
const int N = 500, M = 4e3, inf = 1e9 + 1;
 
struct Edge {
    int u, f = 0, c;
    Edge() {}
    Edge(int u, int c) : u {u}, c {c} {}
};
 
int n, m, k, dist[N], fi[N];
Edge edges[M];
vector<int> g[N];
 
void add_edge(int a, int b) {
    edges[k] = Edge(b, 1);
    edges[k + 1] = Edge(a, 0);
    edges[k + 2] = Edge(a, 1);
    edges[k + 3] = Edge(b, 0);
    g[a].push_back(k);
    g[b].push_back(k + 1);
    g[b].push_back(k + 2);
    g[a].push_back(k + 3);
    k += 4;
}
 
bool bfs() {
    queue<int> q;
    memset(dist, -1, n * sizeof(int));
    dist[0] = 0;
    q.push(0);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(int e : g[v]) {
            auto [u, f, c] = edges[e];
            if(c == f || dist[u] != -1) continue;
            dist[u] = 1 + dist[v];
            q.push(u);
        }
    }
    return dist[n - 1] != -1;
}
 
int dfs(int v, int x = inf) {
    if(!x || v == n - 1) return x;
    for(int& i = fi[v]; i < int(size(g[v])); ++i) {
        int e = g[v][i];
        auto [u, f, c] = edges[e];
        if(dist[v] + 1 != dist[u] || c == f) continue;
        int z = dfs(u, min(x, c - f));
        if(!z) continue;
        edges[e].f += z;
        edges[e ^ 1].f -= z;
        return z;
    }
    return 0;
}
 
void cut() {
    while(bfs()) {
        memset(fi, 0, n * sizeof(int));
        while(dfs(0));
    }
 
    set<ii> S;
 
    for(int v = 0; v < n; ++v) {
        if(dist[v] < 0) continue;
        for(int e : g[v]) {
            int u = edges[e].u;
            if(dist[u] >= 0) continue;
            S.insert({v + 1, u + 1});
        }
    }
 
    cout << size(S) << '\n';
    for(auto [u, v] : S) cout << u << ' ' << v << '\n';
}
 
void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        add_edge(a, b);
    }
    
    cut();
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
