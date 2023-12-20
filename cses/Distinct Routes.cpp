#include "bits/stdc++.h"
using namespace std;
 
using ii = pair<int, int>;
 
const int N = 500, M = 2e3, inf = 1e9 + 1;
 
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
    g[a].push_back(k);
    g[b].push_back(k + 1);
    k += 2;
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
 
int flow() {
    int f = 0;
    while(bfs()) {
        memset(fi, 0, n * sizeof(int));
        for(int x; (x = dfs(0));) f += x;
    }
    return f;
}
 
void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add_edge(a - 1, b - 1);
    }
 
    int f = flow();
 
    cout << f << '\n';
 
    memset(fi, 0, n * sizeof(int));
 
    while(f--) {
        int v = 0;
 
        vector<int> S {1};
 
        while(v != n - 1) {
            for(int& k = fi[v]; k < (int)g[v].size(); ++k) {
                int e = g[v][k];
                auto &[u, f, c] = edges[e];
                if(!c || c != f) continue;
                --f;
                S.push_back(u + 1);
                v = u;
                break;
            }
        }
 
        cout << size(S) << '\n';
        for(int v : S) cout << v << ' ';
        cout<<'\n';
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
