#include "bits/stdc++.h"
using namespace std;
 
using ii = pair<int, int>;
 
const int inf = 1e9;
 
struct Edge {
    int u, cap, flow {}, weight;
    Edge(int u, int cap, int weight) : u(u), cap(cap), weight(weight) {}
};
 
struct MCMF {
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> pi, dist;
    vector<ii> to;
    vector<bool> seen;
    int n, m = 0, s, t;
   
    MCMF(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        pi.resize(n);
        dist.resize(n);
        to.resize(n);
        seen.resize(n);
    }
 
    void add_edge(int v, int u, int cap, int weight) {
        edges.emplace_back(u, cap, weight);
        edges.emplace_back(v, 0, -weight);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
 
    void bellman_ford() {
        queue<int> q;
        vector<bool> in_queue(n, false);
        fill(pi.begin(), pi.end(), inf);
        q.push(s);
        pi[s] = 0;  
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            in_queue[v] = false;
            for(int e : adj[v]) {
                auto [u, cap, flow, weight] = edges[e];
                if(cap - flow <= 0) continue;
                int cost = pi[v] + weight;
                if(pi[u] > cost) {
                    pi[u] = cost;
                    if(!in_queue[u]) {
                        in_queue[u] = true;
                        q.push(u);
                    }
                }
            }
        }
    }
    
    void dijkstra() {
        priority_queue<ii> pq;
        pq.push({0, s});
        for(int v = 0; v < n; ++v) {
            seen[v] = false;
            dist[v] = inf;
        }
        dist[s] = 0;
        while(!pq.empty()) {
            auto [c, v] = pq.top();
            pq.pop();
            if(seen[v]) continue;
            seen[v] = true;
            for(int e : adj[v]) {
                auto [u, cap, flow, weight] = edges[e];
                int cost = dist[v] + weight + pi[v] - pi[u];
                if(cap - flow <= 0 || dist[u] <= cost) continue;
                dist[u] = cost;
                to[u] = {v, e};
                pq.push({-cost, u});    
            }
        }
    }
        
   auto min_cost_max_flow() {
      int cost, flow;
      cost = flow = 0;
      bellman_ford();
       for(;;) {
            dijkstra();
            
            if(dist[t] == inf) break;
     
            int f = inf;
            
            for(int v = t; v != s; v = to[v].first) {
                int e = to[v].second;
                f = min(f, edges[e].cap - edges[e].flow);
            }
            
            for(int v = t; v != s; v = to[v].first) {
                int e = to[v].second;
                edges[e].flow     += f;
                edges[e ^ 1].flow -= f;
            }
            
            cost += f * (dist[t] - pi[s] + pi[t]);
            flow += f;
 
            for(int i = 0; i < n; ++i) pi[i] += dist[i];
       }
        return make_pair(cost, flow);
    }
};
 
void solve() {
    int n;
    cin >> n;
 
    MCMF g(2 * n + 2, 2 * n, 2 * n + 1);
 
    for(int i = 0; i < n; ++i) {
        g.add_edge(2 * n, i, 1, 0);
        for(int j = n; j < 2 * n; ++j) {
            int c;
            cin >> c;
            g.add_edge(i, j, 1, c);
        }
    }
 
    for(int i = n; i < 2 * n; ++i) g.add_edge(i, 2 * n + 1, 1, 0);
 
    auto [custo, fluxo] = g.min_cost_max_flow();
 
    cout << custo << '\n';
 
    vector<ii> ed;
 
    for(int v = 0; v < n; ++v) {
        for(int e : g.adj[v]) {
            auto [u, c, f, w] = g.edges[e];
            if(!c || c != f) continue;
            ed.emplace_back(v + 1, u - n + 1);
        }
    }
 
    for(auto [x, y] : ed) cout << x << ' ' << y << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
